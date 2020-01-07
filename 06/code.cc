#include "code.h"
#include <bitset>
#include <regex>

const std::unordered_map<std::string, std::string> Code::dest_dict_ = {   
    {"null",	"000"},
    {"M",	    "001"},
    {"D",	    "010"},
    {"MD",	    "011"},
    {"A",	    "100"},
    {"AM",	    "101"},
    {"AD",	    "110"},
    {"AMD",	    "111"}
};

const std::unordered_map<std::string, std::string> Code::comp_dict_ = {   
    {"0",   "0101010"},  
    {"1",   "0111111"},
    {"-1",  "0111010"},
    {"D",   "0001100"},
    {"A",   "0110000"},
    {"!D",  "0001101"},
    {"!A",  "0110001"},
    {"-D",  "0001111"},
    {"-A",  "0110011"},
    {"D+1",	"0011111"},
    {"A+1",	"0110111"},
    {"D-1",	"0001110"},
    {"A-1",	"0110010"},
    {"D+A",	"0000010"},
    {"D-A",	"0010011"},
    {"A-D",	"0000111"},
    {"D&A",	"0000000"},
    {"D|A",	"0010101"},
    {"M",	"1110000"},
    {"!M",	"1110001"},
    {"-M",	"1110011"},
    {"M+1",	"1110111"},
    {"M-1",	"1110010"},
    {"D+M",	"1000010"},
    {"D-M",	"1010011"},
    {"M-D",	"1000111"},
    {"D&M",	"1000000"},
    {"D|M",	"1010101"}
};

const std::unordered_map<std::string, std::string> Code::jump_dict_ = {   
    {"null",	"000"},
    {"JGT",	    "001"},
    {"JEQ",	    "010"},
    {"JGE",	    "011"},
    {"JLT",	    "100"},
    {"JNE",	    "101"},
    {"JLE",	    "110"},
    {"JMP",	    "111"}
};

const std::string Code::c_command_pre_ = "111";

bool Code::dest(const std::string& dest, std::string& out) const
{
    const auto it = dest_dict_.find(dest);
    if (it == dest_dict_.cend())
    {
        return false;
    }
    out = it->second;
    return true;
}

bool Code::comp(const std::string& comp, std::string& out) const
{
    const auto it = comp_dict_.find(comp);
    if (it == comp_dict_.cend())
    {
        return false;
    }
    out = it->second;
    return true;
}

bool Code::jump(const std::string& jump, std::string& out) const
{
    const auto it = jump_dict_.find(jump);
    if (it == jump_dict_.cend())
    {
        return false;
    }
    out = it->second;
    return true;
}

bool Code::symbol(unsigned short command, std::string& out) const
{
    std::bitset<16>  bits(command);
    out = bits.to_string();
    return true;
}
