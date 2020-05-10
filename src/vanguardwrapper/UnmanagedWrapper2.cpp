#pragma once

#include <qapplication.h>
#include "UnmanagedWrapper.h"
#include "citra_qt/main.h"

//C++/CLI has various restrictions (no std::mutex for example), so we can't actually include certain headers directly
//What we CAN do is wrap those functions

static GMainWindow* GetMainWindow() {
    for (QWidget* w : qApp->topLevelWidgets()) {
        if (GMainWindow* main = qobject_cast<GMainWindow*>(w)) {
            return main;
        }
    }
    return nullptr;
}

void UnmanagedWrapper::VANGUARD_STOPGAME() {
    GetMainWindow()->ShutdownGame();
}
void UnmanagedWrapper::VANGUARD_LOADGAME(const std::string& file) {
    GetMainWindow()->BootGame(QString::fromStdString(file));
}
