#ifndef __CODE_H__
#define __CODE_H__

#include <unordered_map>
#include <string>

class Code final
{
    public:
        Code() = default;
        ~Code() = default;
        Code(const Code&) = delete;
        Code& operator= (const Code&) = delete;

    public:
        bool dest(const std::string&, std::string&) const;
        bool comp(const std::string&, std::string&) const;
        bool jump(const std::string&, std::string&) const;
        bool symbol(unsigned short, std::string&) const;

    private:
        static const std::unordered_map<std::string, std::string>    dest_dict_;
        static const std::unordered_map<std::string, std::string>    comp_dict_;
        static const std::unordered_map<std::string, std::string>    jump_dict_;
        static const std::string c_command_pre_;
};

#endif 
