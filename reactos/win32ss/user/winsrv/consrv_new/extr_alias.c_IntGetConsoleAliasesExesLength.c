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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {struct TYPE_3__* Next; int /*<<< orphan*/  lpExeName; } ;
typedef  TYPE_1__* PALIAS_HEADER ;

/* Variables and functions */
 int wcslen (int /*<<< orphan*/ ) ; 

UINT
IntGetConsoleAliasesExesLength(PALIAS_HEADER RootHeader)
{
    UINT length = 0;

    while (RootHeader)
    {
        length += (wcslen(RootHeader->lpExeName) + 1) * sizeof(WCHAR);
        RootHeader = RootHeader->Next;
    }
    if (length)
        length += sizeof(WCHAR); // last entry entry is terminated with 2 zero bytes

    return length;
}