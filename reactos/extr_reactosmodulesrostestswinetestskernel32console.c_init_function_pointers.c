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
 void* pGetConsoleInputExeNameA ; 
 void* pGetConsoleProcessList ; 
 void* pOpenConsoleW ; 
 void* pSetConsoleInputExeNameA ; 
 void* pVerifyConsoleIoHandle ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hKernel32;

#define KERNEL32_GET_PROC(func)                                     \
    p##func = (void *)GetProcAddress(hKernel32, #func);             \
    if(!p##func) trace("GetProcAddress(hKernel32, '%s') failed\n", #func);

    hKernel32 = GetModuleHandleA("kernel32.dll");
    KERNEL32_GET_PROC(GetConsoleInputExeNameA);
    KERNEL32_GET_PROC(GetConsoleProcessList);
    KERNEL32_GET_PROC(OpenConsoleW);
    KERNEL32_GET_PROC(SetConsoleInputExeNameA);
    KERNEL32_GET_PROC(VerifyConsoleIoHandle);

#undef KERNEL32_GET_PROC
}