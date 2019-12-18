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
 void* pGetComputerNameExA ; 
 void* pGetComputerNameExW ; 
 void* pGetUserProfileDirectoryA ; 
 void* pOpenProcessToken ; 

__attribute__((used)) static void init_functionpointers(void)
{
    HMODULE hkernel32 = GetModuleHandleA("kernel32.dll");
    HMODULE hadvapi32 = GetModuleHandleA("advapi32.dll");
    HMODULE huserenv = LoadLibraryA("userenv.dll");

    pGetComputerNameExA = (void *)GetProcAddress(hkernel32, "GetComputerNameExA");
    pGetComputerNameExW = (void *)GetProcAddress(hkernel32, "GetComputerNameExW");
    pOpenProcessToken = (void *)GetProcAddress(hadvapi32, "OpenProcessToken");
    pGetUserProfileDirectoryA = (void *)GetProcAddress(huserenv,
                                                       "GetUserProfileDirectoryA");
}