#include "server.h"
#include "camera.h"
#include "client.h"

Server::Server(Camera *camera) : listeningPipe(SERVER_LISTENING_PIPE_PATH, false)
{
    setCamera(camera);
}

Server::~Server()
{
    stop();
}

void Server::stop()
{
    listeningPipe.remove();
    clients_lock.lock();
    while ( !clients.empty())
    {
        (clients.front())->disconnect();
        clients.pop_front();
    }
    clients_lock.unlock();
}

void Server::cmdsInit()
{
    cmds.clear();
    cmdsInfo.clear();
    cmds_internal.clear();

    for (int i = 0; i < supported_cmds_num; i++)
    {
        const Cmd *c = supported_cmds+i;

        cmds.put(c->cmd_name, c->cmd_func);
        cmdsInfo.append(c->cmd_name + '\t' + c->cmd_arg + '\t' + c->cmd_result + '\t' + c->cmd_desc + '\n');
    }

    cmds_internal.put("help", &Server::help_cmd);
}

bool Server::run()
{
    if (!cameraAvailable() || !startServer())
        return false;

    cmdsInit();

    while (1)
    {
        Client_Smart_Ptr new_client = waitingClient();

        if (new_client != NULL)
        {
            clients_lock.lock();
            clients.push_back(new_client);
            clients_lock.unlock();
            boost::thread serviceThread(&Server::serveClient, this, new_client);
        }
        else
            break;
    }

    stop();

    return true;
}

bool Server::startServer()
{
    if (listeningPipe.exist() || listeningPipe.make())
        return true;
    else
        return false;
}

Client_Smart_Ptr Server::waitingClient()
{

    if (!listeningPipe.open())    // blocked until client connected
        return Client_Smart_Ptr();

    std::string clientPrivatePipesDir;
    listeningPipe.readLineTo(clientPrivatePipesDir);

    Client_Smart_Ptr client(new Client(clientPrivatePipesDir));

    listeningPipe.close();

    return client;
}

void Server::serveClient(Client_Smart_Ptr client)  // executes in separate thread
{
    if (!client->connect()) // blocked until client connected
    {
        return;
    }

    std::string cmd;

    client->getCommand(cmd);
    while (!cmd.empty())
    {
        client->sendCommandResult(execCommand(cmd));
        client->getCommand(cmd);
    }

    client->disconnect();
    clients_lock.lock();
    clients.remove(client);
    clients_lock.unlock();
}

std::string Server::execCommand(std::string &cmd) const
{
    std::string cmd_name;
    std::string cmd_arg;

    cmdSplit(cmd, cmd_name, cmd_arg);

    cmd_internal_func_type cmd_int_func = cmds_internal.get<cmd_internal_func_type>(cmd_name, NULL);
    if (cmd_int_func)
        return (this->*cmd_int_func)(cmd_arg);

    cmd_func_type cmd_func = cmds.get<cmd_func_type>(cmd_name, NULL);

    boost::lock_guard<boost::mutex> guard(cam->cam_mutex);
    if (cmd_func)
        return cmd_func(cmd_arg, cam);
    else
        return cmd_inval_func(cmd_arg, cam);
}

void Server::cmdSplit(std::string &cmd, std::string &cmd_name, std::string &cmd_arg) const
{
    std::stringstream ss(cmd);

    ss >> cmd_name;
    ss >> cmd_arg;
}

const std::string &Server::help_cmd(std::string &) const
{
    return getCommandsInfo();
}
