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
 void* p___mb_cur_max_func ; 
 void* p__crtGetStringTypeW ; 
 void* p__p___mb_cur_max ; 
 void* pmemcpy_s ; 

__attribute__((used)) static void init(void)
{
    HMODULE hmod = GetModuleHandleA("msvcrt.dll");

    p__crtGetStringTypeW = (void*)GetProcAddress(hmod, "__crtGetStringTypeW");
    pmemcpy_s = (void*)GetProcAddress(hmod, "memcpy_s");
    p___mb_cur_max_func = (void*)GetProcAddress(hmod, "___mb_cur_max_func");
    p__p___mb_cur_max = (void*)GetProcAddress(hmod, "__p___mb_cur_max");
}