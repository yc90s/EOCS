#include "code_writer.h"

std::unordered_map<std::string, CodeWriter::OpCodeFunc> CodeWriter::optables_ = {
    {"add", &CodeWriter::op_add},
    {"sub", &CodeWriter::op_sub},
    {"neg", &CodeWriter::op_neg},
    {"eq", &CodeWriter::op_eq},
    {"gt", &CodeWriter::op_gt},
    {"lt", &CodeWriter::op_lt},
    {"and", &CodeWriter::op_and},
    {"or", &CodeWriter::op_or},
    {"not", &CodeWriter::op_not},
    {"push", &CodeWriter::op_push},
    {"pop", &CodeWriter::op_pop}
};

std::unordered_map<std::string, CodeWriter::TranslateSegmentFunc> CodeWriter::translate_segment_tables_ = {
    {"argument", &CodeWriter::translate_argument},
    {"local", &CodeWriter::translate_local},
    {"static", &CodeWriter::translate_static},
    {"constant", &CodeWriter::translate_constant},
    {"this", &CodeWriter::translate_this},
    {"that", &CodeWriter::translate_that},
    {"pointer", &CodeWriter::translate_pointer},
    {"temp", &CodeWriter::translate_temp}
};

CodeWriter::CodeWriter(const std::string& output_file)
    : fs_(output_file, std::fstream::out | std::fstream::trunc),
      branch_label_no_(0),
      continue_label_no_(0)
{
}

CodeWriter::~CodeWriter()
{
    if (fs_.is_open())
    {
        fs_.close();
    }
}

void CodeWriter::set_file_name(const std::string& filename)
{
    std::size_t pos = filename.find_last_of(".");
    curr_vm_file_name_ = filename.substr(0, pos);
}

bool CodeWriter::write_arithmetic(const std::string& command)
{
    assert(fs_.is_open() && !curr_vm_file_name_.empty());
    auto func = optables_.find(command);
    if (func == optables_.end())
    {
        return false;
    }

    CommandArgs args;
    return (this->*(func->second))(args);
}

bool CodeWriter::write_push_pop(const std::string& opcode, const std::string& segment, int index)
{
    assert(fs_.is_open() && !curr_vm_file_name_.empty());
    auto func = optables_.find(opcode);
    if (func == optables_.end())
    {
        return false;
    }

    CommandArgs args;
    args.segment = segment;
    args.index = index;
    return (this->*(func->second))(args);
}

bool CodeWriter::translate_segment(CommandArgs const& args)
{
    auto func = translate_segment_tables_.find(args.segment);
    if (func == translate_segment_tables_.end())
    {
        return false;
    }

    (this->*(func->second))(args);
    return true;
}

void CodeWriter::translate_argument(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n" <<
"\
D=A\n\
@ARG\n\
A=M+D\n\
A=M\n\
";
}

void CodeWriter::translate_local(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n" <<
"\
D=A\n\
@LCL\n\
A=M+D\n\
A=M\n\
";
}

void CodeWriter::translate_static(CommandArgs const& args)
{
    fs_ << "@" << curr_vm_file_name_ << "." << args.index << "\n";
}

void CodeWriter::translate_constant(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n";
}

void CodeWriter::translate_this(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n" <<
"\
D=A\n\
@THIS\n\
A=M+D\n\
A=M\n\
";
}

void CodeWriter::translate_that(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n" <<
"\
D=A\n\
@THAT\n\
A=M+D\n\
A=M\n\
";
}

void CodeWriter::translate_pointer(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n" <<
"\
D=A\n\
@THIS\n\
A=D+A\n\
A=M\n\
";
}

void CodeWriter::translate_temp(CommandArgs const& args)
{
    fs_ << "@" << args.index << "\n" <<
"\
D=A\n\
@5\n\
A=D+A\n\
A=M\n\
";
}

HackCodeWriter::HackCodeWriter(const std::string& output_file)
    : CodeWriter(output_file)
{
}

bool HackCodeWriter::op_add(CommandArgs const&)
{
    fs_ << 
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
M=D+M\n\
@SP\n\
M=M+1\n\
";
    return true;
}

bool HackCodeWriter::op_sub(CommandArgs const&)
{
    fs_ << 
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
M=M-D\n\
@SP\n\
M=M+1\n\
";
    return true;
}

bool HackCodeWriter::op_neg(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
M=-M\n\
@SP\n\
M=M+1\n\
";
    return true;
}

bool HackCodeWriter::op_eq(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
D=M-D\n\
"   
    << "@branch_label_" << branch_label_no_ << "\n" <<
"\
D;JEQ\n\
@SP\n\
A=M\n\
M=0\n\
"
    << "@continue_label_" << continue_label_no_ << "\n" << 
"0;JMP\n"

    << "(branch_label_" << branch_label_no_ << ")\n" <<
"\
@SP\n\
A=M\n\
M=-1\n\
"
    << "(continue_label_" << continue_label_no_ << ")\n" <<
"\
@SP\n\
M=M+1\n\
";
    branch_label_no_++;
    continue_label_no_++;
    return true;
}

bool HackCodeWriter::op_gt(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
D=M-D\n\
"   
    << "@branch_label_" << branch_label_no_ << "\n" <<
"\
D;JGT\n\
@SP\n\
A=M\n\
M=0\n\
"
    << "@continue_label_" << continue_label_no_ << "\n" <<
"0;JMP\n"

    << "(branch_label_" << branch_label_no_ << ")\n" <<
"\
@SP\n\
A=M\n\
M=-1\n\
"
    << "(continue_label_" << continue_label_no_ << ")\n" <<
"\
@SP\n\
M=M+1\n\
";
    branch_label_no_++;
    continue_label_no_++;
    return true;
}

bool HackCodeWriter::op_lt(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
D=M-D\n\
"   
    << "@branch_label_" << branch_label_no_ << "\n" <<
"\
D;JLT\n\
@SP\n\
A=M\n\
M=0\n\
"
    << "@continue_label_" << continue_label_no_ << "\n" << 
"0;JMP\n"

    << "(branch_label_" << branch_label_no_ << ")\n" <<
"\
@SP\n\
A=M\n\
M=-1\n\
"
    << "(continue_label_" << continue_label_no_ << ")\n" << 
"\
@SP\n\
M=M+1\n\
";
    branch_label_no_++;
    continue_label_no_++;
    return true;
}

bool HackCodeWriter::op_and(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
M=D&M\n\
@SP\n\
M=M+1\n\
";
    return true;
}

bool HackCodeWriter::op_or(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SP\n\
M=M-1\n\
A=M\n\
M=D|M\n\
@SP\n\
M=M+1\n\
";
    return true;
}


bool HackCodeWriter::op_not(CommandArgs const&)
{
    fs_ <<
"\
@SP\n\
M=M-1\n\
A=M\n\
M=!M\n\
@SP\n\
M=M+1\n\
";
    return true;
}

bool HackCodeWriter::op_push(CommandArgs const& args)
{
    if (!translate_segment(args))
    {
        return false;
    }

    if (args.segment == "constant")
    {
        fs_ << "D=A\n";
    }
    else
    {
        fs_ << "D=M\n";
    }

    fs_ <<
"\
@SP\n\
A=M\n\
M=D\n\
@SP\n\
M=M+1\n\
";
    return true;
}

bool HackCodeWriter::op_pop(CommandArgs const& args)
{
    if (args.segment == "constant" || !translate_segment(args))
    {
        return false;
    }

    fs_ << 
"\
D=A\n\
@SP\n\
M=M-1\n\
A=M\n\
D=D+A\n\
A=D-A\n\
D=D-A\n\
M=D\n\
";

    return true;
}
