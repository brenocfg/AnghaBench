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
struct TYPE_7__ {scalar_t__ LineUpPressed; } ;
struct TYPE_6__ {scalar_t__ NumEntries; scalar_t__ Position; int /*<<< orphan*/ * Entries; } ;
typedef  int /*<<< orphan*/ * PUNICODE_STRING ;
typedef  TYPE_1__* PHISTORY_BUFFER ;
typedef  TYPE_2__* PCONSRV_CONSOLE ;
typedef  size_t INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_1__* HistoryCurrentBuffer (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlPrefixUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ TRUE ; 

BOOL
HistoryFindEntryByPrefix(PCONSRV_CONSOLE Console,
                         PUNICODE_STRING ExeName,
                         PUNICODE_STRING Prefix,
                         PUNICODE_STRING Entry)
{
    INT HistPos;

    /* Search for history entries starting with input. */
    PHISTORY_BUFFER Hist = HistoryCurrentBuffer(Console, ExeName);
    if (!Hist || Hist->NumEntries == 0) return FALSE;

    /*
     * Like Up/F5, on first time start from current (usually last) entry,
     * but on subsequent times start at previous entry.
     */
    if (Console->LineUpPressed)
        Hist->Position = (Hist->Position ? Hist->Position : Hist->NumEntries) - 1;
    Console->LineUpPressed = TRUE;

    // Entry.Length = Console->LinePos * sizeof(WCHAR); // == Pos * sizeof(WCHAR)
    // Entry.Buffer = Console->LineBuffer;

    /*
     * Keep going backwards, even wrapping around to the end,
     * until we get back to starting point.
     */
    HistPos = Hist->Position;
    do
    {
        if (RtlPrefixUnicodeString(Prefix, &Hist->Entries[HistPos], FALSE))
        {
            Hist->Position = HistPos;
            *Entry = Hist->Entries[HistPos];
            return TRUE;
        }
        if (--HistPos < 0) HistPos += Hist->NumEntries;
    } while (HistPos != Hist->Position);

    return FALSE;
}