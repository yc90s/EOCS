#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream>
#include "command.h"
#include "code.h"
#include "symbol.h"

class Parser final 
{
    public:
        Parser(const std::string& prog);
        ~Parser();
        Parser(Parser const&) = delete;
        Parser& operator= (Parser const&) = delete;

    public:
        bool has_more_commands() const;    

        // read next commands if has more commands
        void advance();             

        const CommandType command_type() const;

        // only for A_COMMAND or L_COMMAND, return command's symbol
        const std::string symbol() const;   

        // for C_COMMAND
        const std::string dest() const;

        const std::string comp() const;

        const std::string jump() const;

        bool encode(const Code&, Symbol&, std::string&);

        const std::string& command_string() const;

    private:
        std::fstream                fs_;
        std::shared_ptr<Command>    curr_command_;
        unsigned int                command_count_;
};

#endif
