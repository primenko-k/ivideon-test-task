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

bool Server::run()
{
    if (!cameraAvailable() || !startServer())
        return false;

    while (1)
    {
        Client_Smart_Ptr new_client = waitingClient();

        if (new_client != NULL)
        {
            boost::thread *serviceThread = new boost::thread(&Server::serveClient, this, new_client);
            serveThreads.add_thread(serviceThread);
        }
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

}
