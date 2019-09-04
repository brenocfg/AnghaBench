#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int TickCountQuad; int TickCountMultiplier; } ;
typedef  int LONG ;
typedef  TYPE_1__ KSHARED_USER_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pNtGetTickCount () ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_NtGetTickCount(void)
{
#ifndef _WIN64
    KSHARED_USER_DATA *user_shared_data = (void *)0x7ffe0000;
    LONG diff;
    int i;

    if (!pNtGetTickCount)
    {
        win_skip("NtGetTickCount is not available\n");
        return;
    }

    for (i = 0; i < 5; ++i)
    {
        diff = (user_shared_data->TickCountQuad * user_shared_data->TickCountMultiplier) >> 24;
        diff = pNtGetTickCount() - diff;
        ok(diff < 32, "NtGetTickCount - TickCountQuad too high, expected < 32 got %d\n", diff);
        Sleep(50);
    }
#endif
}