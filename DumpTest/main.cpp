#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

typedef void* (*CalculateFunc)(ULONG_PTR);

int main(void) {
    // DLL 로드
    HMODULE hModule = LoadLibrary(TEXT("FuncDll.dll"));
    if (hModule == NULL) {
        cout << "DLL을 로드할 수 없습니다." << endl;
        return 1;
    }

    // Calculate 함수의 주소 가져오기
    CalculateFunc Calculate = (CalculateFunc)GetProcAddress(hModule, "Calculate");
    if (Calculate == NULL) {
        cout << "Calculate 함수를 찾을 수 없습니다." << endl;
        FreeLibrary(hModule);
        return 1;
    }

    // Calculate 함수 호출
    ULONG_PTR input = 12345;
    void* result = Calculate(input);
    cout << "Calculate 함수의 결과: " << result << endl;

    // DLL 언로드
    FreeLibrary(hModule);

    return 0;
}
