#include "client.h"
#include <cstdlib>
#include <boost/filesystem.hpp> // needs to add -lboost_filesystem and -lboost_system to compiler options

Client::Client() : pipeIn(false), pipeOut(true)
{
    char tmp[] = CLIENT_PIPE_DIR_PATTERN;
    pipeDirName = mkdtemp(tmp);

    pipeIn.make(pipeInPathInner());
    pipeOut.make(pipeOutPathInner());
}

Client::~Client()
{
    disconnect();
}

bool Client::connect()
{
    pipeIn.open();
    pipeOut.open();

    if (!pipeIn.opened() || !pipeOut.opened())
        return false;
    else
        return true;
}

void Client::disconnect()
{
    pipeIn.close();
    pipeOut.close();
    if (boost::filesystem::exists(pipeDirName))
        boost::filesystem::remove_all(pipeDirName);
}

std::string Client::getCommand()
{
    return pipeIn.readLine();
}

void Client::sendCommandResult(const std::string &cmd_result)
{
    pipeOut.writeLine(cmd_result);
}
