#ifndef SERVER_H
#define SERVER_H

#include "commands.h"
#include "pipeline.h"
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp> // needs to add -lboost_thread and -lboost_system to compiler options

#define SERVER_LISTENING_PIPE_PATH  "/tmp/cam_server"

class Camera;
class Client;

typedef boost::shared_ptr<Client> Client_Smart_Ptr;

class Server
{
public:
    Server(Camera *camera = NULL);
    ~Server();

    void setCamera(Camera *camera) { cam = camera; }
    bool cameraAvailable() { return (cam != NULL); }

    bool run();
    void stop();

private:
    bool startServer();
    Client_Smart_Ptr waitingClient();
    void serveClient(Client_Smart_Ptr client);

private:
    Camera *cam;
    Pipeline listeningPipe;
    boost::thread_group serveThreads;
};

#endif // SERVER_H
