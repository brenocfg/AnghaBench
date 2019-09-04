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
 void* pAddDllDirectory ; 
 void* pGetDllDirectoryA ; 
 void* pGetDllDirectoryW ; 
 void* pK32GetModuleInformation ; 
 void* pRemoveDllDirectory ; 
 void* pSetDefaultDllDirectories ; 
 void* pSetDllDirectoryA ; 

__attribute__((used)) static void init_pointers(void)
{
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");

#define MAKEFUNC(f) (p##f = (void*)GetProcAddress(hKernel32, #f))
    MAKEFUNC(GetDllDirectoryA);
    MAKEFUNC(GetDllDirectoryW);
    MAKEFUNC(SetDllDirectoryA);
    MAKEFUNC(AddDllDirectory);
    MAKEFUNC(RemoveDllDirectory);
    MAKEFUNC(SetDefaultDllDirectories);
    MAKEFUNC(K32GetModuleInformation);
#undef MAKEFUNC

    /* before Windows 7 this was not exported in kernel32 */
    if (!pK32GetModuleInformation)
    {
        HMODULE hPsapi = LoadLibraryA("psapi.dll");
        pK32GetModuleInformation = (void *)GetProcAddress(hPsapi, "GetModuleInformation");
    }
}