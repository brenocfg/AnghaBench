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
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ok_str (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
test_p()
{
    char buffer[64];

    sprintf(buffer, "%p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, "00123ABC");

    sprintf(buffer, "%#p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, "0X00123ABC");

    sprintf(buffer, "%#012p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, "  0X00123ABC");

    sprintf(buffer, "%9p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, " 00123ABC");

    sprintf(buffer, "%09p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, " 00123ABC");

    sprintf(buffer, "% 9p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, " 00123ABC");

    sprintf(buffer, "%-9p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, "00123ABC ");

    sprintf(buffer, "%4p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, "00123ABC");

    sprintf(buffer, "%9.4p", (void*)(ptrdiff_t)0x123abc);
    ok_str(buffer, " 00123ABC");

    sprintf(buffer, "%I64p", 0x123abc456789ULL);
    ok_str(buffer, "123ABC456789");

    sprintf(buffer, "%hp", 0x123abc);
    ok_str(buffer, "00003ABC");

}