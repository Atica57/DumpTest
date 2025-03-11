#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

typedef void* (*CalculateFunc)(ULONG_PTR);

int main(void) {
    // DLL �ε�
    HMODULE hModule = LoadLibrary(TEXT("FuncDll.dll"));
    if (hModule == NULL) {
        cout << "DLL�� �ε��� �� �����ϴ�." << endl;
        return 1;
    }

    // Calculate �Լ��� �ּ� ��������
    CalculateFunc Calculate = (CalculateFunc)GetProcAddress(hModule, "Calculate");
    if (Calculate == NULL) {
        cout << "Calculate �Լ��� ã�� �� �����ϴ�." << endl;
        FreeLibrary(hModule);
        return 1;
    }

    // Calculate �Լ� ȣ��
    ULONG_PTR input = 12345;
    void* result = Calculate(input);
    cout << "Calculate �Լ��� ���: " << result << endl;

    // DLL ��ε�
    FreeLibrary(hModule);

    return 0;
}
