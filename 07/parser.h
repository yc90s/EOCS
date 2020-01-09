#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream>
#include "command.h"

// hardware platform independent 
class Parser final
{
    public:
        Parser(const std::string& prog);
        ~Parser();
        Parser(const Parser&) = delete;
        Parser& operator= (const Parser&) = delete;

    public:
        bool            has_more_commands() const;
        void            advance();
        const CommandType     command_type() const;
        const std::string     arg1() const;
        int                   arg2() const;        

    public:
        const std::string& command_string() const;
        const std::string& op_code() const;

    private:
        std::fstream                fs_;        
        std::shared_ptr<Command>    curr_command_;
};

#endif
