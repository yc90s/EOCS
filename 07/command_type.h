#ifndef __COMMAND_TYPE_H__
#define __COMMAND_TYPE_H__

#include <memory>

class Command;
enum class CommandType : unsigned char
{
    C_ARITHMETIC = 0,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
    NONE_COMMAND    
};

std::shared_ptr<Command> create_command(const std::string&, const std::string&);

#endif
