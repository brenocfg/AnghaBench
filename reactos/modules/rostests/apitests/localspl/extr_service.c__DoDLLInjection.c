#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pe ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int dwSize; int /*<<< orphan*/  th32ProcessID; int /*<<< orphan*/  szExeFile; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__ PROCESSENTRY32W ;
typedef  int /*<<< orphan*/  LPTHREAD_START_ROUTINE ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateRemoteThread (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleW (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 scalar_t__ OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/  Process32FirstW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ Process32NextW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  TH32CS_SNAPPROCESS ; 
 scalar_t__ VirtualAllocEx (scalar_t__,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteProcessMemory (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wcsicmp (int /*<<< orphan*/ ,char*) ; 
 int wcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcsrchr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
_DoDLLInjection()
{
    DWORD cbDLLPath;
    HANDLE hProcess;
    HANDLE hSnapshot;
    HANDLE hThread;
    PROCESSENTRY32W pe;
    PVOID pLoadLibraryAddress;
    PVOID pLoadLibraryArgument;
    PWSTR p;
    WCHAR wszFilePath[MAX_PATH];

    // Get the full path to our EXE file.
    if (!GetModuleFileNameW(NULL, wszFilePath, _countof(wszFilePath)))
    {
        DPRINT("GetModuleFileNameW failed with error %lu!\n", GetLastError());
        return;
    }

    // Replace the extension.
    p = wcsrchr(wszFilePath, L'.');
    if (!p)
    {
        DPRINT("File path has no file extension: %S\n", wszFilePath);
        return;
    }

    wcscpy(p, L".dll");
    cbDLLPath = (wcslen(wszFilePath) + 1) * sizeof(WCHAR);

    // Create a snapshot of the currently running processes.
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        DPRINT("CreateToolhelp32Snapshot failed with error %lu!\n", GetLastError());
        return;
    }

    // Enumerate through all running processes.
    pe.dwSize = sizeof(pe);
    if (!Process32FirstW(hSnapshot, &pe))
    {
        DPRINT("Process32FirstW failed with error %lu!\n", GetLastError());
        return;
    }

    do
    {
        // Check if this is the spooler server process.
        if (wcsicmp(pe.szExeFile, L"spoolsv.exe") != 0)
            continue;

        // Open a handle to the process.
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
        if (!hProcess)
        {
            DPRINT("OpenProcess failed with error %lu!\n", GetLastError());
            return;
        }

        // Get the address of LoadLibraryW.
        pLoadLibraryAddress = (PVOID)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryW");
        if (!pLoadLibraryAddress)
        {
            DPRINT("GetProcAddress failed with error %lu!\n", GetLastError());
            return;
        }

        // Allocate memory for the DLL path in the spooler process.
        pLoadLibraryArgument = VirtualAllocEx(hProcess, NULL, cbDLLPath, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (!pLoadLibraryArgument)
        {
            DPRINT("VirtualAllocEx failed with error %lu!\n", GetLastError());
            return;
        }

        // Write the DLL path to the process memory.
        if (!WriteProcessMemory(hProcess, pLoadLibraryArgument, wszFilePath, cbDLLPath, NULL))
        {
            DPRINT("WriteProcessMemory failed with error %lu!\n", GetLastError());
            return;
        }

        // Create a new thread in the spooler process that calls LoadLibraryW as the start routine with our DLL as the argument.
        // This effectively injects our DLL into the spooler process and we can inspect localspl.dll there just like the spooler.
        hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibraryAddress, pLoadLibraryArgument, 0, NULL);
        if (!hThread)
        {
            DPRINT("CreateRemoteThread failed with error %lu!\n", GetLastError());
            return;
        }

        CloseHandle(hThread);
        break;
    }
    while (Process32NextW(hSnapshot, &pe));
}