#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_11__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_12__ {struct TYPE_12__* Flink; } ;
struct TYPE_14__ {TYPE_2__ HistoryBuffers; } ;
struct TYPE_13__ {int /*<<< orphan*/  ExeName; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  TYPE_3__* PHISTORY_BUFFER ;
typedef  TYPE_4__* PCONSRV_CONSOLE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_3__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConsoleFreeHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConvertInputAnsiToUnicode (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HISTORY_BUFFER ; 
 int /*<<< orphan*/  ListEntry ; 
 scalar_t__ RtlPrefixUnicodeString (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static PHISTORY_BUFFER
HistoryFindBuffer(PCONSRV_CONSOLE Console,
                  PVOID    ExeName,
                  USHORT   ExeLength,
                  BOOLEAN  UnicodeExe)
{
    UNICODE_STRING ExeNameU;

    PLIST_ENTRY Entry;
    PHISTORY_BUFFER Hist = NULL;

    if (ExeName == NULL) return NULL;

    if (UnicodeExe)
    {
        ExeNameU.Buffer = ExeName;
        /* Length is in bytes */
        ExeNameU.MaximumLength = ExeLength;
    }
    else
    {
        if (!ConvertInputAnsiToUnicode(Console,
                                       ExeName, ExeLength,
                                       &ExeNameU.Buffer, &ExeNameU.MaximumLength))
        {
            return NULL;
        }
    }
    ExeNameU.Length = ExeNameU.MaximumLength;

    Entry = Console->HistoryBuffers.Flink;
    while (Entry != &Console->HistoryBuffers)
    {
        Hist = CONTAINING_RECORD(Entry, HISTORY_BUFFER, ListEntry);

        /* For the history APIs, the caller is allowed to give only part of the name */
        if (RtlPrefixUnicodeString(&ExeNameU, &Hist->ExeName, TRUE))
        {
            if (!UnicodeExe) ConsoleFreeHeap(ExeNameU.Buffer);
            return Hist;
        }

        Entry = Entry->Flink;
    }

    if (!UnicodeExe) ConsoleFreeHeap(ExeNameU.Buffer);
    return NULL;
}