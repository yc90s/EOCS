#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include <memory>
#include "code.h"
#include "symbol.h"

enum class CommandType : unsigned char 
{
    A_COMMAND = 0,      // @Xxx
    C_COMMAND = 1,      // dest=comp;jump
    L_COMMAND = 2,      // (Xxx)
    NONE_COMMAND,
};

class Command
{
    public:
        Command(const std::string& command_string);
        virtual ~Command() = default;
        Command(const Command&) = delete;
        Command& operator= (const Command&) = delete;

    public:
        static std::shared_ptr<Command> create_command(const std::string& command_string);
        const std::string& command_string() const { return origin_command_; }

    public:
        virtual const CommandType command_type() const = 0;
        virtual bool encode(const Code&, Symbol&, unsigned int, std::string&) = 0;
        virtual const std::string symbol() const { return std::string(); }
        virtual const std::string dest() const { return std::string(); }
        virtual const std::string comp() const { return std::string(); }
        virtual const std::string jump() const { return std::string(); }

    protected:
        bool check_symbol_valid() const;

    protected:
        std::string command_;
        std::string origin_command_;
};

class ACommand: public Command
{
    public:
        ACommand(const std::string& command_string);
        ~ACommand() = default;
        ACommand(const ACommand&) = delete;
        ACommand& operator= (const ACommand&) = delete;

    public:
        const CommandType command_type() const override;
        bool encode(const Code&, Symbol&, unsigned int, std::string&) override;
        const std::string symbol() const override;
};

class CCommand: public Command
{
    public:
        CCommand(const std::string& command_string);
        ~CCommand() = default;
        CCommand(const CCommand&) = delete;
        CCommand& operator= (const CCommand&) = delete;

    public:
        const CommandType command_type() const override;
        bool encode(const Code&, Symbol&, unsigned int, std::string&) override;
        const std::string dest() const override;
        const std::string comp() const override;
        const std::string jump() const override;

    private:
        std::string     dest_;
        std::string     comp_;
        std::string     jump_;
        std::string     pre_;
};

class LCommand: public Command
{
    public:
        LCommand(const std::string& command_string);
        ~LCommand() = default;
        LCommand(const LCommand&) = delete;
        LCommand& operator= (const LCommand&) = delete;

    public:
        const CommandType command_type() const override;
        bool encode(const Code&, Symbol&, unsigned int, std::string&) override;
        const std::string symbol() const override;
};

#endif 
