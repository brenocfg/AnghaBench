#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/  lpSource; } ;
struct TYPE_5__ {TYPE_2__* Data; } ;
typedef  TYPE_1__* PALIAS_HEADER ;
typedef  TYPE_2__* PALIAS_ENTRY ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
IntInsertAliasEntry(PALIAS_HEADER Header, PALIAS_ENTRY NewEntry)
{
    PALIAS_ENTRY CurrentEntry;
    PALIAS_ENTRY *LastLink = &Header->Data;

    while ((CurrentEntry = *LastLink) != NULL)
    {
        INT Diff = _wcsicmp(NewEntry->lpSource, CurrentEntry->lpSource);
        if (Diff < 0) break;

        LastLink = &CurrentEntry->Next;
    }

    *LastLink = NewEntry;
    NewEntry->Next = CurrentEntry;
}