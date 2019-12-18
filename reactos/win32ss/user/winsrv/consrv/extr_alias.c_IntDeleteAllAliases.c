#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {struct TYPE_7__* Next; struct TYPE_7__* Data; } ;
struct TYPE_6__ {TYPE_2__* Aliases; } ;
typedef  TYPE_1__* PCONSRV_CONSOLE ;
typedef  TYPE_2__* PALIAS_HEADER ;
typedef  TYPE_2__* PALIAS_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleFreeHeap (TYPE_2__*) ; 

VOID
IntDeleteAllAliases(PCONSRV_CONSOLE Console)
{
    PALIAS_HEADER Header, NextHeader;
    PALIAS_ENTRY Entry, NextEntry;

    for (Header = Console->Aliases; Header; Header = NextHeader)
    {
        NextHeader = Header->Next;
        for (Entry = Header->Data; Entry; Entry = NextEntry)
        {
            NextEntry = Entry->Next;
            ConsoleFreeHeap(Entry);
        }
        ConsoleFreeHeap(Header);
    }
}