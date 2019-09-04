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
 void* p_makepath_s ; 
 void* p_searchenv_s ; 
 void* p_wmakepath_s ; 
 void* p_wsearchenv_s ; 

__attribute__((used)) static void init(void)
{
    HMODULE hmod = GetModuleHandleA("msvcrt.dll");

    p_makepath_s = (void *)GetProcAddress(hmod, "_makepath_s");
    p_wmakepath_s = (void *)GetProcAddress(hmod, "_wmakepath_s");
    p_searchenv_s = (void *)GetProcAddress(hmod, "_searchenv_s");
    p_wsearchenv_s = (void *)GetProcAddress(hmod, "_wsearchenv_s");
}