#include "command.h"
#include <unordered_map>
#include <functional>

using CreateCommandByTypeFunc = std::function<std::shared_ptr<Command>(const std::string&)>;

struct CommandTypeHasher
{
    std::size_t operator() (const CommandType& type) const
    {
        return std::hash<unsigned char>{}(static_cast<unsigned char>(type));
    }
};

struct CommandTypeCompare
{
    bool operator()(const CommandType& type1, const CommandType& type2) const
    {
        return static_cast<unsigned char>(type1) == static_cast<unsigned char>(type2);
    }
};

static std::unordered_map<CommandType, CreateCommandByTypeFunc, CommandTypeHasher, CommandTypeCompare>  type_to_command_dict = {
    {CommandType::C_ARITHMETIC, [](const std::string& command_string){ return std::make_shared<ArithmeticCommand>(command_string); }},
    {CommandType::C_PUSH, [](const std::string& command_string){ return std::make_shared<PushCommand>(command_string); }},
    {CommandType::C_POP, [](const std::string& command_string){ return std::make_shared<PopCommand>(command_string); }}
};

static std::unordered_map<std::string, CommandType> opcode_to_command_type_dict = {
    {"add", CommandType::C_ARITHMETIC},
    {"sub", CommandType::C_ARITHMETIC},
    {"neg", CommandType::C_ARITHMETIC},
    {"eq", CommandType::C_ARITHMETIC},
    {"gt", CommandType::C_ARITHMETIC},
    {"lt", CommandType::C_ARITHMETIC},
    {"and", CommandType::C_ARITHMETIC},
    {"or", CommandType::C_ARITHMETIC},
    {"not", CommandType::C_ARITHMETIC},
    {"push", CommandType::C_PUSH},
    {"pop", CommandType::C_POP}
};

std::shared_ptr<Command> create_command(const std::string& op, const std::string& command_string)
{
    auto opit = opcode_to_command_type_dict.find(op);
    if (opit == opcode_to_command_type_dict.end())
    {
        return nullptr;
    }

    auto command_it = type_to_command_dict.find(opit->second);
    if (command_it == type_to_command_dict.end())
    {
        return nullptr;
    }
    return command_it->second(command_string);
}
