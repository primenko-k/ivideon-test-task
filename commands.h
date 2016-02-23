#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

/*
 * To add new command support, just define function of 'cmd_func_type' type and
 * add 'Cmd' element with a pointer to this function to 'supported_cmds' array.
 */

class Camera;

typedef std::string (*cmd_func_type)(std::string &arg, Camera *cam);

struct Cmd {
    std::string cmd_name;
    std::string cmd_arg;
    std::string cmd_result;
    std::string cmd_desc;
    cmd_func_type cmd_func;
};

extern const Cmd supported_cmds[];
extern const int supported_cmds_num;

extern std::string cmd_inval_func(std::string &arg, Camera *cam);

#endif // COMMANDS_H
