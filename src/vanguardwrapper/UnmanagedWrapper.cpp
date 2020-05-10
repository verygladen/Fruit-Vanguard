#pragma once

#include "UnmanagedWrapper.h"
#include "core/core.h"
#include "Vanguard/VanguardClient.h"
#include <thread>
#include <chrono>

//C++/CLI has various restrictions (no std::mutex for example), so we can't actually include certain headers directly
//What we CAN do is wrap those functions

bool UnmanagedWrapper::savestate_done = false;

void UnmanagedWrapper::VANGUARD_EXIT() {
    //wxGetApp().Exit();
}

std::string GetSaveStatePath(u64 program_id, u32 slot) {
    return fmt::format("{}{:016X}.{:02d}.cst", FileUtil::GetUserPath(FileUtil::UserPath::StatesDir),
                       program_id, slot);
}

std::string UnmanagedWrapper::VANGUARD_GETGAMENAME() {
    std::string title;
    Core::System::GetInstance().GetAppLoader().ReadTitle(title);
    return title;
}

void UnmanagedWrapper::VANGUARD_LOADSTATE(const std::string& file) {
    u64 title_id;
    if (Core::System::GetInstance().GetAppLoader().ReadProgramId(title_id) == Loader::ResultStatus::
        Success) {

        if (!FileUtil::Copy(file, GetSaveStatePath(title_id, 9))) {
            LOG_ERROR(Core, "Could not copy file for loadstate{}", file);
            return;
        }
    }
    Core::System::GetInstance().SendSignal(Core::System::Signal::Load, 9);
}

std::string UnmanagedWrapper::VANGUARD_SAVESTATE(const std::string& file) {

    Core::System::GetInstance().SendSignal(Core::System::Signal::Save, 9);

    u64 title_id;
    if (Core::System::GetInstance().GetAppLoader().ReadProgramId(title_id) ==
        Loader::ResultStatus::Success) {

        /*if (!FileUtil::Copy(GetSaveStatePath(title_id, 9), file)) {
            LOG_ERROR(Core, "Could not copy file for savestate{}", file);
            return;
        }*/
        return GetSaveStatePath(title_id, 9);
    }
    return "";
}

void UnmanagedWrapper::VANGUARD_LOADSTATE_DONE() {

    VanguardClientUnmanaged::LOAD_STATE_DONE();
}
void UnmanagedWrapper::VANGUARD_SAVESTATE_DONE() {

    VanguardClientUnmanaged::SAVE_STATE_DONE();
}

void UnmanagedWrapper::VANGUARD_RESUMEEMULATION() {
    //GetCoreThread().Resume();
}

void UnmanagedWrapper::PADDR_POKEBYTE(long long addr, unsigned char val) {
    auto ptr = Core::System::GetInstance().Memory().GetPhysicalRef(0x20000000).GetPtr();
    std::memcpy(ptr + addr, &val, sizeof(u8));
}

unsigned char UnmanagedWrapper::PADDR_PEEKBYTE(long long addr) {
    auto ptr = Core::System::GetInstance().Memory().GetPhysicalRef(0x20000000).GetPtr();
    u8 value;
    std::memcpy(&value, ptr + addr, sizeof(u8));
    return value;
    return 0;
}

std::string UnmanagedWrapper::VANGUARD_SAVECONFIG() {
    return "";
}

void UnmanagedWrapper::VANGUARD_LOADCONFIG(std::string cfg) {
}

void UnmanagedWrapper::VANGUARD_CORESTEP() {
    VanguardClientUnmanaged::CORE_STEP();
}

void UnmanagedWrapper::LOAD_STATE_DONE() {

    VanguardClientUnmanaged::LOAD_STATE_DONE();
}
