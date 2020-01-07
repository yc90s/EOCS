#include "command.h"
#include <regex>

Command::Command(const std::string& command_string)
    : command_(command_string),
      origin_command_(command_string)
{
    assert(!command_.empty());
}

std::shared_ptr<Command> Command::create_command(const std::string& command_string)
{
    assert(!command_string.empty());
    switch (command_string[0])
    {
    case '@':
        return std::make_shared<ACommand>(command_string);
    case '(':
        return std::make_shared<LCommand>(command_string);
    default:
        return std::make_shared<CCommand>(command_string);
    }
}

bool Command::check_symbol_valid() const
{
    std::regex symbol_reg("^[[:alpha:]_\\.\\$:]+[\\w_\\.\\$:]*");
    return std::regex_match(command_, symbol_reg);
}

ACommand::ACommand(const std::string& command_string)
    : Command(command_string)
{
    command_.erase(0, 1);
}

const CommandType ACommand::command_type() const
{
    return CommandType::A_COMMAND;
}

bool ACommand::encode(const Code& code, Symbol& symbols, unsigned int, std::string& out)
{
    std::regex digit_reg("^\\d*");
    bool is_digit = std::regex_match(command_, digit_reg);
    bool is_symbol = check_symbol_valid();
    if (!is_digit && !is_symbol)
    {
        return false;
    }


    unsigned short cmd = 0;
    if (is_digit)
    {
        // digit
        cmd = std::stoul(command_);
    }
    else 
    {
        // symbol
        if (!symbols.contains(command_))
        {
            // add new symbols
            symbols.add_entry(command_);
        }
        cmd = symbols.get_address(command_);
    }

    bool result = code.symbol(cmd, out);
    out += "\n";
    return result;
}

const std::string ACommand::symbol() const
{
    return command_;
}

CCommand::CCommand(const std::string& command_string)
    : Command(command_string),
      pre_("111")
{
    // dest=comp;jump
    std::regex reg("((A?M?D?)=)?([^?;]+)(;([A-Z]+))?");
    std::smatch result;
    std::regex_match(command_, result, reg);
    if (result[2].matched)
    {
        dest_ = result[2];
    }
    else
    {
        dest_ = "null";
    }
    comp_ = result[3];
    if (result[5].matched)
    {
        jump_ = result[5];
    }
    else
    {
        jump_ = "null";
    }
}

const CommandType CCommand::command_type() const
{
    return CommandType::C_COMMAND;
}

bool CCommand::encode(const Code& code, Symbol&, unsigned int, std::string& out)
{
    std::string dest_out, comp_out, jump_out;
    if (!code.dest(dest(), dest_out))
    {
        return false;
    }
    if (!code.comp(comp(), comp_out))
    {
        return false;
    }
    if (!code.jump(jump(), jump_out))
    {
        return false;
    }
    out = pre_ + comp_out + dest_out + jump_out + "\n";
    return true;
}

const std::string CCommand::dest() const
{
    return dest_;
}

const std::string CCommand::comp() const
{
    return comp_;
}

const std::string CCommand::jump() const
{
    return jump_;
}

LCommand::LCommand(const std::string& command_string)
    : Command(command_string)
{
    command_ = command_.substr(1, command_string.length() - 2);
}

const CommandType LCommand::command_type() const
{
    return CommandType::L_COMMAND;
}

bool LCommand::encode(const Code&, Symbol& symbol, unsigned int curr_command_count, std::string& out)
{
    if (!check_symbol_valid())
    {
        return false;
    }
    if (symbol.contains(command_))
    {
        return false;    
    }
    out.clear();
    symbol.add_entry(command_, curr_command_count);
    return true;
}

const std::string LCommand::symbol() const
{
    return command_;
}
