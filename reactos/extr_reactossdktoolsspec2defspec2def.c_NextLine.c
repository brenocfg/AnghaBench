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

/* Variables and functions */

char *
NextLine(char *pc)
{
    while (*pc != 0)
    {
        if (pc[0] == '\n' && pc[1] == '\r') return pc + 2;
        else if (pc[0] == '\n') return pc + 1;
        pc++;
    }
    return pc;
}