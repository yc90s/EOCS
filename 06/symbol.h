#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <unordered_map>
#include <string>

class Symbol final
{
    public:
        Symbol(unsigned short base_addr = 16);
        ~Symbol() = default;
        Symbol(const Symbol&) = delete;
        Symbol& operator= (const Symbol&) = delete;

    public:
        void add_entry(const std::string&);
        void add_entry(const std::string&, unsigned short);
        bool contains(const std::string&) const;
        unsigned short get_address(const std::string&) const;

    private:
        unsigned short  base_addr_;
        unsigned short  curr_addr_;
        std::unordered_map<std::string, unsigned short>     symbols_;
};

#endif 
