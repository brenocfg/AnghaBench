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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  HistoryBuffers; } ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  int /*<<< orphan*/  PHISTORY_BUFFER ;
typedef  TYPE_1__* PCONSRV_CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HISTORY_BUFFER ; 
 int /*<<< orphan*/  HistoryDeleteBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 

VOID
HistoryDeleteBuffers(PCONSRV_CONSOLE Console)
{
    PLIST_ENTRY CurrentEntry;
    PHISTORY_BUFFER HistoryBuffer;

    while (!IsListEmpty(&Console->HistoryBuffers))
    {
        CurrentEntry = RemoveHeadList(&Console->HistoryBuffers);
        HistoryBuffer = CONTAINING_RECORD(CurrentEntry, HISTORY_BUFFER, ListEntry);
        HistoryDeleteBuffer(HistoryBuffer);
    }
}