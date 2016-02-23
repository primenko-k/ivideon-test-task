#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "pipeline.h"

#define CLIENT_PIPE_DIR_PATTERN "/tmp/cam-XXXXXX"
#define CLIENT_PIPE_IN_NAME "out.pipe" // <inner IN > <=> <outter OUT>
#define CLIENT_PIPE_OUT_NAME "in.pipe" // <inner OUT> <=> <outter IN >

class Client
{
public:
    Client();
    ~Client();

    std::string pipeInPath() { return pipeOutPathInner(); }
    std::string pipeOutPath(){ return pipeInPathInner(); }

    bool connect(); // may block
    void disconnect();
    std::string getCommand();
    void sendCommandResult(const std::string &cmd_result);

private:
    std::string pipeInPathInner() { return (pipeDirName + '/' + CLIENT_PIPE_IN_NAME); }
    std::string pipeOutPathInner(){ return (pipeDirName + '/' + CLIENT_PIPE_OUT_NAME); }

private:
    std::string pipeDirName;
    Pipeline pipeIn, pipeOut;
};

#endif // CLIENT_H
