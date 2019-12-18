#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_3__ {int wDest; size_t dwFlag; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 TYPE_1__* g_Flags ; 

__attribute__((used)) static DWORD ValidateFlags(DWORD GlobalFlags, WORD Dest)
{
    DWORD n;
    DWORD Valid = 0;

    for (n = 0; n < ARRAYSIZE(g_Flags); ++n)
    {
        if (g_Flags[n].wDest & Dest)
        {
            Valid |= g_Flags[n].dwFlag;
        }
    }

    return GlobalFlags & Valid;
}