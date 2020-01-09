#include "command.h"
#include <regex>

Command::Command(const std::string& command_string)
    : command_(command_string),
      op_(command_string)
{
}

std::shared_ptr<Command> Command::create_command(const std::string& command_string)
{
    auto pos = command_string.find_first_of(" ");
    return ::create_command(command_string.substr(0, pos), command_string);
}

UnaryCommand::UnaryCommand(const std::string& command_string)
    : Command(command_string)
{
    std::regex  reg("^([a-z]+) +(.+)");
    std::smatch result;
    std::regex_match(command_, result, reg);
    op_ = result[1];
    arg1_ = result[2];
}

const std::string UnaryCommand::arg1() const
{
    return arg1_;
}

BinaryCommand::BinaryCommand(const std::string& command_string)
    : Command(command_string)
{
    std::regex  reg("^([a-z]+) +([^ ]+) +(\\d+)");
    std::smatch result;
    std::regex_match(command_, result, reg);
    op_ = result[1];
    arg1_ = result[2];
    arg2_ = std::stoi(result[3]);
}

const std::string BinaryCommand::arg1() const
{
    return arg1_;
}

int BinaryCommand::arg2() const
{
    return arg2_;
}

ArithmeticCommand::ArithmeticCommand(const std::string& command_string)
    : Command(command_string),
      arg1_(command_)
{
}


const CommandType ArithmeticCommand::command_type() const
{
    return CommandType::C_ARITHMETIC;
}

const std::string ArithmeticCommand::arg1() const
{
    return arg1_;
}

PushCommand::PushCommand(const std::string& command_string)
    : BinaryCommand(command_string)
{
}

const CommandType PushCommand::command_type() const
{
    return CommandType::C_PUSH;
}

PopCommand::PopCommand(const std::string& command_string)
    : BinaryCommand(command_string)
{
}

const CommandType PopCommand::command_type() const
{
    return CommandType::C_POP;
}
