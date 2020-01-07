#include "symbol.h"

Symbol::Symbol(unsigned short base_addr)
    : base_addr_(base_addr),
      curr_addr_(base_addr_)
{
    symbols_["SP"] = 0;
    symbols_["LCL"] = 1;
    symbols_["ARG"] = 2;
    symbols_["THIS"] = 3;
    symbols_["THAT"] = 4;
    symbols_["SCREEN"] = 16384;
    symbols_["KBD"] = 24576;
    symbols_["R0"] = 0;
    symbols_["R1"] = 1;
    symbols_["R2"] = 2;
    symbols_["R3"] = 3;
    symbols_["R4"] = 4;
    symbols_["R5"] = 5;
    symbols_["R6"] = 6;
    symbols_["R7"] = 7;
    symbols_["R8"] = 8;
    symbols_["R9"] = 9;
    symbols_["R10"] = 10;
    symbols_["R11"] = 11;
    symbols_["R12"] = 12;
    symbols_["R13"] = 13;
    symbols_["R14"] = 14;
    symbols_["R15"] = 15;
}

void Symbol::add_entry(const std::string& symbol)
{
    assert(contains(symbol) == false);
    symbols_[symbol] = curr_addr_;
    curr_addr_++;
}

void Symbol::add_entry(const std::string& symbol, unsigned short addr)
{
    assert(contains(symbol) == false);
    symbols_[symbol] = addr;
}

bool Symbol::contains(const std::string& symbol) const
{
    const auto it = symbols_.find(symbol);
    return it != symbols_.cend();
}

unsigned short Symbol::get_address(const std::string& symbol) const
{
    assert(contains(symbol));
    const auto it = symbols_.find(symbol);
    return it->second;
}
