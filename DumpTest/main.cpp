#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

typedef void* (*CalculateFunc)(ULONG_PTR);
typedef void* (*PrintStringFunc)();

int main(void) {
    // DLL 로드
    HMODULE hModule = LoadLibrary(TEXT("FuncDll.dll"));
    if (hModule == NULL) {
        cout << "Cannot load dll" << endl;
        return 1;
    }

    // Calculate 함수의 주소 가져오기
    CalculateFunc Calculate = (CalculateFunc)GetProcAddress(hModule, "Calculate");
    if (Calculate == NULL) {
        cout << "Cannot find Calculate function" << endl;
        FreeLibrary(hModule);
        return 1;
    }

    // Calculate 함수 호출
    ULONG_PTR input = 0x1234;
    void* result = Calculate(input);
    cout << "The result of Calculate : " << result << endl;

    //print string variable
    PrintStringFunc PrintString = (PrintStringFunc)GetProcAddress(hModule, "PrintString");  
    if (PrintString == NULL) {
		cout << "Cannot find PrintString function" << endl;
		FreeLibrary(hModule);
		return 1;
	}
    // PrintString 함수 호출
    PrintString();

    // DLL 언로드
    FreeLibrary(hModule);

    return 0;
}
