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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 void* pCheckTokenMembership ; 
 void* pConvertSidToStringSidA ; 
 void* pGetNativeSystemInfo ; 
 void* pGetSystemInfo ; 
 void* pGetSystemWow64DirectoryA ; 
 void* pIsWow64Process ; 
 void* pMsiGetComponentPathExA ; 
 void* pOpenProcessToken ; 
 void* pRegDeleteKeyExA ; 
 void* pRegDeleteKeyExW ; 
 void* pSHGetFolderPathA ; 
 void* pSRRemoveRestorePoint ; 
 void* pSRSetRestorePointA ; 

__attribute__((used)) static void init_functionpointers(void)
{
    HMODULE hmsi = GetModuleHandleA("msi.dll");
    HMODULE hadvapi32 = GetModuleHandleA("advapi32.dll");
    HMODULE hkernel32 = GetModuleHandleA("kernel32.dll");
    HMODULE hshell32 = GetModuleHandleA("shell32.dll");
    HMODULE hsrclient;

#define GET_PROC(mod, func) \
    p ## func = (void*)GetProcAddress(mod, #func);

    GET_PROC(hmsi, MsiGetComponentPathExA);
    GET_PROC(hshell32, SHGetFolderPathA);

    GET_PROC(hadvapi32, CheckTokenMembership);
    GET_PROC(hadvapi32, ConvertSidToStringSidA);
    GET_PROC(hadvapi32, OpenProcessToken);
    GET_PROC(hadvapi32, RegDeleteKeyExA)
    GET_PROC(hadvapi32, RegDeleteKeyExW)
    GET_PROC(hkernel32, IsWow64Process)
    GET_PROC(hkernel32, GetNativeSystemInfo)
    GET_PROC(hkernel32, GetSystemInfo)
    GET_PROC(hkernel32, GetSystemWow64DirectoryA)

    hsrclient = LoadLibraryA("srclient.dll");
    GET_PROC(hsrclient, SRRemoveRestorePoint);
    GET_PROC(hsrclient, SRSetRestorePointA);
#undef GET_PROC
}