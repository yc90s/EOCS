#include "parser.h"
#include <algorithm>

Parser::Parser(const std::string& prog)
    : curr_command_(nullptr),
      command_count_(0)
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
        // erase all whitespace
        command_string.erase(std::remove_if(command_string.begin(), command_string.end(), isspace), command_string.end());

        if (!command_string.empty())
        {
            curr_command_ = Command::create_command(command_string);
            if (command_type() == CommandType::A_COMMAND || command_type() == CommandType::C_COMMAND)
            {
                command_count_++;
            }
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

const std::string Parser::symbol() const
{
    assert(curr_command_ != nullptr);
    return curr_command_->symbol();
}

const std::string Parser::dest() const
{
    assert(curr_command_ != nullptr);
    return curr_command_->dest();
}

const std::string Parser::comp() const
{
    assert(curr_command_ != nullptr);
    return curr_command_->comp();
}

const std::string Parser::jump() const
{
    assert(curr_command_ != nullptr);
    return curr_command_->jump();
}

bool Parser::encode(const Code& code, Symbol& symbols, std::string& out)
{
    assert(curr_command_ != nullptr);
    return curr_command_->encode(code, symbols, command_count_, out);
}

const std::string& Parser::command_string() const
{
    assert(curr_command_ != nullptr);
    return curr_command_->command_string();
}
