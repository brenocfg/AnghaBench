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
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ INT ;

/* Variables and functions */

__attribute__((used)) static void
ReplaceChars(WCHAR *pch, INT Len, WCHAR From, WCHAR To)
{
    while (Len > 0)
    {
        if (*pch == From)
        {
            *pch = To;
        }
        //printf("0x%04X, ", *pch);
        ++pch;
        --Len;
    }
}