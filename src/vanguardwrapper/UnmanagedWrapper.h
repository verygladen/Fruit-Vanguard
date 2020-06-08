#pragma once
#include <string>
#include <mutex>



typedef void (*FnPtr_VanguardMethod)();
class UnmanagedWrapper
{
public:
    static void VANGUARD_EXIT();
    static void VANGUARD_LOADSTATE(const std::string &file);
    static std::string VANGUARD_SAVESTATE(const std::string& file);
    static void VANGUARD_SAVESTATE_DONE();
    static void VANGUARD_LOADSTATE_DONE();
    void VANGUARD_PAUSEEMULATION();
    static void VANGUARD_RESUMEEMULATION();
    static void VANGUARD_STOPGAME();
    static void VANGUARD_LOADGAME(const std::string& file);
    static std::string VANGUARD_GETGAMENAME();
    static void PADDR_POKEBYTE(long long addr, unsigned char val, long offset);
    static unsigned char PADDR_PEEKBYTE(long long addr, long offset);
    static std::string VANGUARD_SAVECONFIG();
    static void VANGUARD_LOADCONFIG(std::string cfg);
    static void VANGUARD_CORESTEP();
    static void LOAD_STATE_DONE();
    static bool IS_N3DS();
    static void SET_N3DS(bool isN3DS);

    static bool savestate_done; //REPLACE THIS
};
