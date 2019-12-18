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
 scalar_t__ IsSeparator (char const) ; 

int
CompareToken(const char *token, const char *comparand)
{
    while (*comparand)
    {
        if (*token != *comparand) return 0;
        token++;
        comparand++;
    }
    if (IsSeparator(comparand[-1])) return 1;
    if (!IsSeparator(*token)) return 0;
    return 1;
}