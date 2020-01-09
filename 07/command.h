#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include "command_type.h"

class Command
{
    public:
        Command(const std::string& command_string);
        virtual ~Command() = default;
        Command(const Command&) = delete;
        Command& operator= (const Command&) = delete;

    public:
        static std::shared_ptr<Command> create_command(const std::string& command_string);
        const std::string& command_string() const { return command_; }
        const std::string& op_code() const { return op_; }

    public:
        virtual const CommandType command_type() const = 0;
        virtual const std::string arg1() const { return ""; }
        virtual int arg2() const { return -1; }

    protected:
        std::string command_;
        std::string op_;        // default i.e. command_
};

class UnaryCommand : public Command
{
    public: 
        UnaryCommand(const std::string& command_string);
        virtual ~UnaryCommand() = default;
        UnaryCommand(const UnaryCommand&) = delete;
        UnaryCommand& operator= (const UnaryCommand&) = delete;

    public:
        const std::string arg1() const override;

    protected:
        std::string arg1_;
};

class BinaryCommand : public Command
{
    public:
        BinaryCommand(const std::string& command_string);
        virtual ~BinaryCommand() = default;
        BinaryCommand(const BinaryCommand&) = delete;
        BinaryCommand& operator= (const BinaryCommand&) = delete;

    public:
        const std::string arg1() const override;
        int arg2() const override;

    protected:
        std::string arg1_;
        int         arg2_;
};

class ArithmeticCommand : public Command
{
    public:
        ArithmeticCommand(const std::string& command_string);
        ~ArithmeticCommand() = default;
        ArithmeticCommand(const ArithmeticCommand&) = delete;
        ArithmeticCommand& operator= (const ArithmeticCommand&) = delete;

    public:
        const CommandType command_type() const override;
        const std::string arg1() const override;

    private:
        std::string     arg1_;
};


class PushCommand : public BinaryCommand
{
    public:
        PushCommand(const std::string& command_string);
        ~PushCommand() = default;
        PushCommand(const PushCommand&) = delete;
        PushCommand& operator= (const PushCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class PopCommand : public BinaryCommand
{
    public:
        PopCommand(const std::string& command_string);
        ~PopCommand() = default;
        PopCommand(const PopCommand&) = delete;
        PopCommand& operator= (const PopCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class LabelCommand : public Command
{
    public:
        LabelCommand(const std::string& command_string);
        ~LabelCommand() = default;
        LabelCommand(const LabelCommand&) = delete;
        LabelCommand& operator= (const LabelCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class GotoCommand : public Command
{
    public:
        GotoCommand(const std::string& command_string);
        ~GotoCommand() = default;
        GotoCommand(const GotoCommand&) = delete;
        GotoCommand& operator= (const GotoCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class IfCommand : public Command
{
    public:
        IfCommand(const std::string& command_string);
        ~IfCommand() = default;
        IfCommand(const IfCommand&) = delete;
        IfCommand& operator= (const IfCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class FunctionCommand : public Command
{
    public:
        FunctionCommand(const std::string& command_string);
        ~FunctionCommand() = default;
        FunctionCommand(const FunctionCommand&) = delete;
        FunctionCommand& operator= (const FunctionCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class ReturnCommand : public Command
{
    public:
        ReturnCommand(const std::string& command_string);
        ~ReturnCommand() = default;
        ReturnCommand(const ReturnCommand&) = delete;
        ReturnCommand& operator= (const ReturnCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

class CallCommand : public Command
{
    public:
        CallCommand(const std::string& command_string);
        ~CallCommand() = default;
        CallCommand(const CallCommand&) = delete;
        CallCommand& operator= (const CallCommand&) = delete;

    public:
        const CommandType command_type() const override;
};

#endif
