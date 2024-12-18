#include "WindowHooker.hpp"
#include "Logger.hpp"
#include "termcolor/termcolor.hpp"
#include <iostream>

using namespace std;

int main() {
    Logger::info("Starting application...");

    // Ask user for target window name
    string windowName;
    Logger::input("Enter the target window name: ");
    getline(cin, windowName);

    // Ask user for DLL name
    string dllName;
    Logger::input("Enter the DLL name (with extension): ");
    getline(cin, dllName);

    // Ask user for exported function name
    string functionName;
    Logger::input("Enter the exported function name: ");
    getline(cin, functionName);

    // Find target window
    HWND hwnd = FindWindow(NULL, windowName.c_str());
    if (!hwnd) {
        Logger::error("Could not find target window: " + windowName);
        return EXIT_FAILURE;
    }
    Logger::success("Found target window: " + windowName);

    // Get thread and process ID
    DWORD pid = 0;
    DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
    if (!tid) {
        Logger::error("Failed to get thread ID of target window.");
        return EXIT_FAILURE;
    }
    Logger::success("Thread ID: " + to_string(tid) + ", Process ID: " + to_string(pid));

    // Load DLL
    HMODULE dll = LoadLibraryEx(dllName.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
    if (!dll) {
        Logger::error("DLL not found: " + dllName);
        return EXIT_FAILURE;
    }
    Logger::success("DLL loaded: " + dllName);

    // Get exported function address
    HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, functionName.c_str());
    if (!addr) {
        Logger::error("Exported function '" + functionName + "' not found in " + dllName);
        return EXIT_FAILURE;
    }
    Logger::success("Exported function '" + functionName + "' address retrieved.");

    // Set hook
    HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid);
    if (!handle) {
        Logger::error("Failed to set hook with SetWindowsHookEx.");
        return EXIT_FAILURE;
    }
    Logger::success("Hook set successfully.");

    // Trigger the hook
    PostThreadMessage(tid, WM_NULL, NULL, NULL);
    Logger::info("Hook triggered.");

    // Wait for user input to remove the hook
    Logger::info("Press any key to unhook and unload the DLL.");
    system("pause > nul");

    // Remove the hook
    if (!UnhookWindowsHookEx(handle)) {
        Logger::error("Failed to remove the hook.");
        return EXIT_FAILURE;
    }
    Logger::success("Hook removed successfully.");

    Logger::info("Application finished. Press any key to exit.");
    system("pause > nul");
    return EXIT_SUCCESS;
}