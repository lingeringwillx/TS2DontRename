#include "utils.h"

DWORD WINAPI MainThread(LPVOID param)
{
    HMODULE module = GetModuleHandleA(NULL);
    char *modBase = (char *)module;

    if (IsLargeAddressAware(modBase))
    {
        unsigned char fun1Bytes[16] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
                                       0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
        WriteToMemory((DWORD)0x00EF2C14, (char*)fun1Bytes, sizeof(fun1Bytes) / sizeof(*fun1Bytes));
    }
    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}