#ifndef SERVER_H
#define SERVER_H

#include "commands.h"
#include "pipeline.h"
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp> // needs to add -lboost_thread and -lboost_system to compiler options
#include <boost/property_tree/ptree.hpp>

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
    std::string execCommand(std::string &cmd) const;

    void cmdsInit();
    void cmdSplit(std::string &cmd, std::string &cmd_name, std::string &cmd_arg) const;
    const std::string & getCommandsInfo() const { return cmdsInfo; }

//  internal command functions
    std::string help_cmd(std::string &arg) const;

private:
    Camera *cam;
    Pipeline listeningPipe;
    std::list<Client_Smart_Ptr> clients;

    std::string cmdsInfo;
    boost::property_tree::basic_ptree<std::string, cmd_func_type> cmds;

    typedef std::string (Server::*cmd_internal_func_type)(std::string &arg) const;
    boost::property_tree::basic_ptree<std::string, cmd_internal_func_type> cmds_internal;
};

#endif // SERVER_H
