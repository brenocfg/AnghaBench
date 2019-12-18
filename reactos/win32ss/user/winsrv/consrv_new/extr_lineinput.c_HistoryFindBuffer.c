#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* Flink; } ;
struct TYPE_10__ {TYPE_1__ HistoryBuffers; } ;
struct TYPE_9__ {int /*<<< orphan*/  ExeName; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  TYPE_2__* PHISTORY_BUFFER ;
typedef  TYPE_3__* PCONSOLE ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HISTORY_BUFFER ; 
 int /*<<< orphan*/  ListEntry ; 
 scalar_t__ RtlPrefixUnicodeString (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static PHISTORY_BUFFER
HistoryFindBuffer(PCONSOLE Console, PUNICODE_STRING ExeName)
{
    PLIST_ENTRY Entry = Console->HistoryBuffers.Flink;
    while (Entry != &Console->HistoryBuffers)
    {
        /* For the history APIs, the caller is allowed to give only part of the name */
        PHISTORY_BUFFER Hist = CONTAINING_RECORD(Entry, HISTORY_BUFFER, ListEntry);
        if (RtlPrefixUnicodeString(ExeName, &Hist->ExeName, TRUE))
            return Hist;
        Entry = Entry->Flink;
    }
    return NULL;
}