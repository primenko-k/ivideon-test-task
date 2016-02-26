#include "client.h"
#include <boost/filesystem.hpp> // needs to add -lboost_filesystem and -lboost_system to compiler options

Client::Client(std::string &pipeDirName) : pipeDirName(pipeDirName), pipeIn(false), pipeOut(true)
{
    pipeIn.make(pipeInPathInner());
    pipeOut.make(pipeOutPathInner());
}

Client::~Client()
{
    disconnect();
}

bool Client::connect()
{
    if (pipeOut.open())
        pipeIn.open();

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

std::string & Client::getCommand(std::string &buf)
{
    return pipeIn.readLineTo(buf);
}

void Client::sendCommandResult(const std::string &cmd_result)
{
    pipeOut.writeLine(cmd_result);
}
