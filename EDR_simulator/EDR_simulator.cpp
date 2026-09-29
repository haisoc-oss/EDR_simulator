// Inline_hook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <winternl.h>
#include <wchar.h>

using NtAllocateVirtualMemory = NTSTATUS(WINAPI*)(HANDLE, PVOID, ULONG_PTR, PSIZE_T, ULONG, ULONG);

typedef NTSTATUS(WINAPI* NtQueryInformationProcess_t)(
    HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
using PrototypeMessageBox = int (WINAPI*)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
PrototypeMessageBox originalMsgBox = MessageBoxA;

int main()
{


    const char* ProcessPath = "E:\\tool\\code\\lastdance.exe";
    //const char* DLL_Path = "E:\\tool\\code\\hello-world-x86.dll";
    const char* DLL_Path = "C:\\Users\\Acer-PC\\source\\repos\\check_check_check\\x64\\Debug\\check_check_check.dll";

    ULONG_PTR ProcID = 18144;

    //get hooked Process handle 
    HANDLE Remote_Proc_Handle = OpenProcess(PROCESS_CREATE_THREAD | 
        PROCESS_QUERY_INFORMATION |
        PROCESS_VM_OPERATION |
        PROCESS_VM_WRITE |
        PROCESS_VM_READ, TRUE, ProcID);

    LPSTARTUPINFOA Start_Up_Info = new STARTUPINFOA();
    PROCESS_BASIC_INFORMATION Basic_info = { 0 };
    PPROCESS_INFORMATION Process_info = new PROCESS_INFORMATION();
    //DWORD size = strlen(ProcessPath);
    DWORD Image_Base;
    LPVOID DLL_Mem_Location;
    //Check_check_check(Remote_Proc_Handle);

    DLL_Mem_Location = VirtualAllocEx(Remote_Proc_Handle, 0, strlen(DLL_Path), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(Remote_Proc_Handle, DLL_Mem_Location, DLL_Path, strlen(DLL_Path), 0);
    //PVOID DLL_HDL = LoadLibraryA(DLL_Path);
    //DWORD a = strlen(DLL_Path);
    PVOID b = GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
    PTHREAD_START_ROUTINE threatStartRoutineAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
    HANDLE DLL_Handle =  CreateRemoteThread(Remote_Proc_Handle, NULL, 0, threatStartRoutineAddress, DLL_Mem_Location, 0, NULL);
    DWORD a = GetProcessId(DLL_Handle);
    CloseHandle(Remote_Proc_Handle);

    //const char* Des_process_Path = "C:\\Users\\Acer-PC\\source\\repos\\direct_indirect_syscall\\x64\\Debug\\direct_indirect_syscall.exe";
    ////const char* DLL_Path = "E:\\tool\\code\\hello-world-x86.dll";
    //const char* DLL_Path = "C:\\Users\\Acer-PC\\source\\repos\\check_check_check\\x64\\Debug\\check_check_check.dll";

    //LPSTARTUPINFOA pStart_up_info = new STARTUPINFOA();
    //LPPROCESS_INFORMATION pProcess_info = new PROCESS_INFORMATION;
    //DWORD Image_Base;
    //LPVOID DLL_Mem_Location;
    //CreateProcessA(Des_process_Path, 0, 0, 0, 0, CREATE_SUSPENDED, 0, 0, pStart_up_info, pProcess_info);
    //if (!pProcess_info->hProcess)
    //{
    //    std::cerr << "Write fail. Error: " << GetLastError() << std::endl;
    //    return 0;
    //}
    //DLL_Mem_Location = VirtualAllocEx(pProcess_info->hProcess, 0, strlen(DLL_Path), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    //WriteProcessMemory(pProcess_info->hProcess, DLL_Mem_Location, DLL_Path, strlen(DLL_Path), 0);
    //PVOID b = GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
    //PTHREAD_START_ROUTINE threatStartRoutineAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
    //HANDLE DLL_Handle = CreateRemoteThread(pProcess_info->hProcess, NULL, 0, threatStartRoutineAddress, DLL_Mem_Location, 0, NULL);
    //DWORD a = GetProcessId(DLL_Handle);
    //ResumeThread(pProcess_info->hThread);
    //CloseHandle(pProcess_info->hProcess);

    //ULONG_PTR ProcID = 21536;

    ////get hooked Process handle 
    //HANDLE Remote_Proc_Handle = OpenProcess(PROCESS_CREATE_THREAD | 
    //    PROCESS_QUERY_INFORMATION |
    //    PROCESS_VM_OPERATION |
    //    PROCESS_VM_WRITE |
    //    PROCESS_VM_READ, TRUE, ProcID);


    //HMODULE hNtdll = LoadLibrary(TEXT("ntdll.dll"));
    //

    //

    //ULONG_PTR Hooked_API_Adress1 = (ULONG_PTR)GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
    //ULONG_PTR Hooked_API_Adress2 = (ULONG_PTR)GetProcAddress(hNtdll, "NtCreateThreadEx");
    //ULONG_PTR Hooked_API_Adress3 = (ULONG_PTR)GetProcAddress(hNtdll, "NtProtectVirtualMemory");
    //PVOID Adress_of_shell = Create_shell(Remote_Proc_Handle, Hooked_API_Adress1);
    //Making_jump(Remote_Proc_Handle, Hooked_API_Adress1, Adress_of_shell);

    /*Check_check_check(Remote_Proc_Handle);
    LPVOID a = VirtualAllocEx(Remote_Proc_Handle, 0, 1024, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    
    Lets_hook(Remote_Proc_Handle, Hooked_API_Adress1,a);
    Lets_hook(Remote_Proc_Handle, Hooked_API_Adress2, a);
    Lets_hook(Remote_Proc_Handle, Hooked_API_Adress3, a);*/
    //alocate memory in hooked process for write shellcode and Tranpoline
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
