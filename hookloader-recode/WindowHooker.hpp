#ifndef WINDOW_HOOKER_HPP
#define WINDOW_HOOKER_HPP

#include <Windows.h>
#include <string>

class WindowHooker {
public:
    static HWND findWindow(const std::string& windowName) {
        return FindWindow(NULL, windowName.c_str());
    }

    static DWORD getThreadProcessId(HWND hwnd, DWORD* pid) {
        return GetWindowThreadProcessId(hwnd, pid);
    }

    static HMODULE loadDll(const std::string& dllName) {
        return LoadLibraryEx(dllName.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
    }

    static HOOKPROC getExportedFunction(HMODULE dll, const std::string& functionName) {
        return (HOOKPROC)GetProcAddress(dll, functionName.c_str());
    }

    static HHOOK setHook(int hookType, HOOKPROC addr, HMODULE dll, DWORD tid) {
        return SetWindowsHookEx(hookType, addr, dll, tid);
    }

    static bool removeHook(HHOOK handle) {
        return UnhookWindowsHookEx(handle);
    }
};

#endif // WINDOW_HOOKER_HPP
