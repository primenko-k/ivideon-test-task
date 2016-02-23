#include "server.h"
#include "camera.h"
#include "client.h"

Server::Server(Camera *camera) : listeningPipe(SERVER_LISTENING_PIPE_PATH, true), serveThreads()
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
    serveThreads.interrupt_all();
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
            boost::thread *serviceThread = new boost::thread(&Server::serveClient, this, new_client);
            serveThreads.add_thread(serviceThread);
        }

        /*
         * Give to a client time to close pipe.
         * So we prevent secondary trigger waitingClient() by the same client.
         */
        boost::this_thread::sleep_for(boost::chrono::milliseconds(40));
    }

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

    listeningPipe.open();    // blocked until client connected

    Client_Smart_Ptr client(new Client);
    if (client)
    {
        std::string clientPrivatePipes = (client->pipeInPath() + " " + client->pipeOutPath());
        listeningPipe.writeLine(clientPrivatePipes);
    }

    listeningPipe.close();

    return client;
}

void Server::serveClient(Client_Smart_Ptr client)  // executes in separate thread
{
    if (!client->connect()) // blocked until client connected
    {
        std::cerr << "Client @" << client << "isnt connected" << std::endl;
        return;
    }

    std::string cmd;

    cmd = client->getCommand();
    while (!cmd.empty())
    {
        client->sendCommandResult(execCommand(cmd));
        cmd = client->getCommand();
    }

    client->disconnect();
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

std::string Server::help_cmd(std::string &) const
{
    return getCommandsInfo();
}
