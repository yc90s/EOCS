#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <functional>

class ScopeGuard final
{
    using Func = std::function<void(void)>;
    public:
    ScopeGuard(const Func& ctor, const Func& dtor)
        : m_ctor(ctor),
        m_dtor(dtor)
    {
        m_ctor();
    }
    ~ScopeGuard()
    {
        m_dtor();
    }
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator= (const ScopeGuard&) = delete;

    private:
    Func  m_ctor;
    Func  m_dtor;
};

#endif
