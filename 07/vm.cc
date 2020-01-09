#include "parser.h"
#include "code_writer.h"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: VM file.vm out.asm" << std::endl;
        return -1;
    }

    Parser parser(argv[1]);
    HackCodeWriter  code_writer(argv[2]);
    code_writer.set_file_name(argv[1]);
    while (parser.has_more_commands())
    {
        parser.advance();
        if (parser.command_type() == CommandType::C_PUSH || parser.command_type() == CommandType::C_POP)
        {
            code_writer.write_push_pop(parser.op_code(), parser.arg1(), parser.arg2());
        }
        else if (parser.command_type() == CommandType::C_ARITHMETIC)
        {
            code_writer.write_arithmetic(parser.op_code());
        }
    }
    return 0;
}
