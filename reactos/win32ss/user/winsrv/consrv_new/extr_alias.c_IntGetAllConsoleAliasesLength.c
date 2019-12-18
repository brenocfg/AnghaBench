#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_5__ {struct TYPE_5__* Next; int /*<<< orphan*/  lpTarget; int /*<<< orphan*/  lpSource; } ;
struct TYPE_4__ {TYPE_2__* Data; } ;
typedef  TYPE_1__* PALIAS_HEADER ;
typedef  TYPE_2__* PALIAS_ENTRY ;

/* Variables and functions */
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 

UINT
IntGetAllConsoleAliasesLength(PALIAS_HEADER Header)
{
    UINT Length = 0;
    PALIAS_ENTRY CurEntry = Header->Data;

    while (CurEntry)
    {
        Length += wcslen(CurEntry->lpSource);
        Length += wcslen(CurEntry->lpTarget);
        Length += 2; // zero byte and '='
        CurEntry = CurEntry->Next;
    }

    if (Length)
    {
        return (Length+1) * sizeof(WCHAR);
    }
    return 0;
}