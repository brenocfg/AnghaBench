#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {scalar_t__ NumEntries; size_t Position; TYPE_1__* Entries; } ;
struct TYPE_7__ {scalar_t__ Length; } ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  TYPE_2__* PHISTORY_BUFFER ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;

/* Variables and functions */
 TYPE_2__* HistoryCurrentBuffer (int /*<<< orphan*/ ,TYPE_1__*) ; 

VOID
HistoryGetCurrentEntry(PCONSRV_CONSOLE Console,
                       PUNICODE_STRING ExeName,
                       PUNICODE_STRING Entry)
{
    PHISTORY_BUFFER Hist = HistoryCurrentBuffer(Console, ExeName);

    if (!Hist || Hist->NumEntries == 0)
        Entry->Length = 0;
    else
        *Entry = Hist->Entries[Hist->Position];
}