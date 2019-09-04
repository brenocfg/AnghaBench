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
 void* pCheckTokenMembership ; 
 void* pIsWow64Process ; 
 void* pOpenProcessToken ; 
 void* pRegDeleteKeyExA ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_functionpointers(void)
{
    HMODULE hadvapi32 = GetModuleHandleA("advapi32.dll");
    HMODULE hkernel32 = GetModuleHandleA("kernel32.dll");

#define GET_PROC(dll, func) \
    p ## func = (void *)GetProcAddress(dll, #func); \
    if(!p ## func) \
      trace("GetProcAddress(%s) failed\n", #func);

    GET_PROC(hadvapi32, CheckTokenMembership);
    GET_PROC(hadvapi32, OpenProcessToken);
    GET_PROC(hadvapi32, RegDeleteKeyExA)
    GET_PROC(hkernel32, IsWow64Process)

#undef GET_PROC
}