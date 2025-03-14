﻿// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

ULONG InitialCookie;
char str[1024] = "[DLL]This is example for memory dump.";

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
		InitialCookie = 0xDADAF00D;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// 임의의 수를 입력받아 출력하는 함수
extern "C" __declspec(dllexport) void* Calculate(ULONG_PTR Context)
{
    WCHAR String[1024];
    swprintf_s(String, ARRAYSIZE(String), L"%s\n", L"FuncDll/Calculate function started");
    OutputDebugStringW(String);

    return (void*)((ULONG_PTR)(Context) ^ InitialCookie);
}

//print dll string variable
extern "C" __declspec(dllexport) void PrintString()
{
	printf("%s\n", str);
}

