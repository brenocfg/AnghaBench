#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pIsWow64Process ; 
 void* pNtQuerySystemInformation ; 
 void* pNtQueryVirtualMemory ; 
 void* pWow64DisableWow64FsRedirection ; 
 void* pWow64RevertWow64FsRedirection ; 

__attribute__((used)) static BOOL init_func_ptrs(void)
{
    pNtQuerySystemInformation = (void *)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQuerySystemInformation");
    pNtQueryVirtualMemory = (void *)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryVirtualMemory");
    pIsWow64Process = (void *)GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsWow64Process");
    pWow64DisableWow64FsRedirection = (void *)GetProcAddress(GetModuleHandleA("kernel32.dll"), "Wow64DisableWow64FsRedirection");
    pWow64RevertWow64FsRedirection = (void *)GetProcAddress(GetModuleHandleA("kernel32.dll"), "Wow64RevertWow64FsRedirection");
    return TRUE;
}