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
 void* p__p__environ ; 
 void* p__p__wenviron ; 
 void* p_environ ; 
 void* p_get_environ ; 
 void* p_get_wenviron ; 
 void* p_wenviron ; 

__attribute__((used)) static void init(void)
{
    HMODULE hmod = GetModuleHandleA("msvcrt.dll");

    p__p__environ = (void *)GetProcAddress(hmod, "__p__environ");
    p__p__wenviron = (void *)GetProcAddress(hmod, "__p__wenviron");
    p_environ = (void *)GetProcAddress(hmod, "_environ");
    p_wenviron = (void *)GetProcAddress(hmod, "_wenviron");
    p_get_environ = (void *)GetProcAddress(hmod, "_get_environ");
    p_get_wenviron = (void *)GetProcAddress(hmod, "_get_wenviron");
}