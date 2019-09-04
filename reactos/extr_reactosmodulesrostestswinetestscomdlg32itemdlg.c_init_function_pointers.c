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
 void* pSHCreateItemFromParsingName ; 
 void* pSHCreateShellItem ; 
 void* pSHGetIDListFromObject ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hmod = GetModuleHandleA("shell32.dll");

#define MAKEFUNC(f) (p##f = (void*)GetProcAddress(hmod, #f))
    MAKEFUNC(SHCreateShellItem);
    MAKEFUNC(SHGetIDListFromObject);
    MAKEFUNC(SHCreateItemFromParsingName);
#undef MAKEFUNC
}