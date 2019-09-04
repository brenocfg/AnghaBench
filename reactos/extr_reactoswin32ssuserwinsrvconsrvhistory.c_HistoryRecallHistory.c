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
typedef  size_t ULONG ;
struct TYPE_3__ {scalar_t__ NumEntries; size_t Position; int /*<<< orphan*/ * Entries; } ;
typedef  int /*<<< orphan*/ * PUNICODE_STRING ;
typedef  TYPE_1__* PHISTORY_BUFFER ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* HistoryCurrentBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  max (size_t,int /*<<< orphan*/ ) ; 
 size_t min (int /*<<< orphan*/ ,scalar_t__) ; 

BOOL
HistoryRecallHistory(PCONSRV_CONSOLE Console,
                     PUNICODE_STRING ExeName,
                     INT Offset,
                     PUNICODE_STRING Entry)
{
    PHISTORY_BUFFER Hist = HistoryCurrentBuffer(Console, ExeName);
    ULONG Position = 0;

    if (!Hist || Hist->NumEntries == 0) return FALSE;

    Position = Hist->Position + Offset;
    Position = min(max(Position, 0), Hist->NumEntries - 1);
    Hist->Position = Position;

    *Entry = Hist->Entries[Hist->Position];
    return TRUE;
}