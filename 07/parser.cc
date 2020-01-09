#include "parser.h"
#include <algorithm>

Parser::Parser(const std::string& prog)
    : curr_command_(nullptr)
{
    fs_.open(prog);
}

Parser::~Parser()
{
    if (fs_.is_open())
    {
        fs_.close();
    }
}

bool Parser::has_more_commands() const
{
    return !fs_.eof();
}

void Parser::advance()
{
    curr_command_ = nullptr;
    std::string command_string;
    while (has_more_commands())
    {
        std::getline(fs_, command_string);

        // erase comments
        auto comments_pos = command_string.find("//");
        if (comments_pos != std::string::npos)
        {
            command_string.erase(comments_pos);
        }
        // erase the leading and trailing whitespaces
        command_string.erase(0, command_string.find_first_not_of(" "));
        command_string.erase(command_string.find_last_not_of(" \r\n") + 1);

        if (!command_string.empty())
        {
            curr_command_ = Command::create_command(command_string);
            break;
        }
    }
}

const CommandType Parser::command_type() const
{
    if (curr_command_)
    {
        return curr_command_->command_type();
    }
    else
    {
        return CommandType::NONE_COMMAND;
    }
}

const std::string Parser::arg1() const
{
    assert(curr_command_);
    return curr_command_->arg1();
}

int Parser::arg2() const
{
    assert(curr_command_);
    return curr_command_->arg2();
}

const std::string& Parser::command_string() const
{
    assert(curr_command_);
    return curr_command_->command_string();
}

const std::string& Parser::op_code() const
{
    assert(curr_command_);
    return curr_command_->op_code();
}
