#pragma once
#include <string>



typedef void (*FnPtr_VanguardMethod)();
class UnmanagedWrapper
{
public:
    static void VANGUARD_EXIT();
    static void VANGUARD_LOADSTATE(const std::string &file);
    static void VANGUARD_SAVESTATE(const std::string& file);
    static void VANGUARD_RESUMEEMULATION();
    static void VANGUARD_STOPGAME();
    static void VANGUARD_LOADGAME(const std::string& file);
    static std::string VANGUARD_GETGAMENAME();
    static void PADDR_POKEBYTE(long long addr, unsigned char val);
    static unsigned char PADDR_PEEKBYTE(long long addr);
    static std::string VANGUARD_SAVECONFIG();
    static void VANGUARD_LOADCONFIG(std::string cfg);
    static void VANGUARD_CORESTEP();
};
