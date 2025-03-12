#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

typedef void* (*CalculateFunc)(ULONG_PTR);

int main(void) {
    // DLL �ε�
    HMODULE hModule = LoadLibrary(TEXT("FuncDll.dll"));
    if (hModule == NULL) {
        cout << "Cannot load dll" << endl;
        return 1;
    }

    // Calculate �Լ��� �ּ� ��������
    CalculateFunc Calculate = (CalculateFunc)GetProcAddress(hModule, "Calculate");
    if (Calculate == NULL) {
        cout << "Cannot find Calculate function" << endl;
        FreeLibrary(hModule);
        return 1;
    }

    // Calculate �Լ� ȣ��
    ULONG_PTR input = 0x1234;
    void* result = Calculate(input);
    cout << "The result of Calculate : " << result << endl;

    // DLL ��ε�
    FreeLibrary(hModule);

    return 0;
}
