#include "parser.h"
#include "util.hpp"
#include <iostream>

std::string output_filename(const char* file)
{
    std::string result = file;
    std::size_t pos = result.find_last_of(".");
    if (pos == std::string::npos)
    {
        result += ".hack";
    }
    else
    {
        result.replace(pos, result.length() - pos, ".hack");
    }

    return result;
}

bool pre_parse(char* filename, Symbol& symbols)
{
    Parser parser(filename);
    Code code;
    std::string out;
    while (parser.has_more_commands())
    {
        parser.advance();
        if (parser.command_type() != CommandType::L_COMMAND)
        {
            continue; 
        }
        if (!parser.encode(code, symbols, out))
        {
            std::cerr << "Invalid command: " << parser.command_string() << std::endl;
            return false;
        }
    }
    return true;
}

bool parse(const char* filename, Symbol& symbols)
{
    Parser  parser(filename);
    Code    code;
    std::string out;
    std::string out_file = output_filename(filename);
    std::fstream wfile(out_file, std::fstream::out | std::fstream::trunc);
    ScopeGuard guard([]{}, [&wfile]{ 
            wfile.close(); 
    });

    while (parser.has_more_commands())
    {
        parser.advance();
        if (parser.command_type() == CommandType::NONE_COMMAND || parser.command_type() == CommandType::L_COMMAND)
        {
            continue;
        }
        if (!parser.encode(code, symbols, out))
        {
            std::cerr << "Invalid command: " << parser.command_string() << std::endl;
            return false;
        }
        wfile << out;
    }
    return true;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: Assemble Hack.asm" << std::endl;
        return -1;        
    }
    Symbol  symbols;
    if (!pre_parse(argv[1], symbols))
    {
        std::cerr << "Pre Parser Failed!" << std::endl;
        return -2;
    }

    if (!parse(argv[1], symbols))
    {
        std::cerr << "Parser Failed!" << std::endl;
        return -3;
    }

    return 0;
}
