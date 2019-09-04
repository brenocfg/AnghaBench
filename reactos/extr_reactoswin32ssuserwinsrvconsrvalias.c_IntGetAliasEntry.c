#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_7__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_9__ {struct TYPE_9__* Next; int /*<<< orphan*/  Source; } ;
struct TYPE_8__ {TYPE_3__* Data; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;
typedef  TYPE_2__* PALIAS_HEADER ;
typedef  TYPE_3__* PALIAS_ENTRY ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleFreeHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConvertInputAnsiToUnicode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlCompareUnicodeString (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static PALIAS_ENTRY
IntGetAliasEntry(PCONSRV_CONSOLE Console,
                 PALIAS_HEADER Header,
                 PVOID    Source,
                 USHORT   SourceLength,
                 BOOLEAN  Unicode)
{
    UNICODE_STRING SourceU;

    PALIAS_ENTRY Entry;
    INT Diff;

    if (Header == NULL || Source == NULL) return NULL;

    if (Unicode)
    {
        SourceU.Buffer = Source;
        /* Length is in bytes */
        SourceU.MaximumLength = SourceLength;
    }
    else
    {
        if (!ConvertInputAnsiToUnicode(Console,
                                       Source, SourceLength,
                                       &SourceU.Buffer, &SourceU.MaximumLength))
        {
            return NULL;
        }
    }
    SourceU.Length = SourceU.MaximumLength;

    Entry = Header->Data;
    while (Entry)
    {
        Diff = RtlCompareUnicodeString(&Entry->Source, &SourceU, TRUE);
        if (!Diff)
        {
            if (!Unicode) ConsoleFreeHeap(SourceU.Buffer);
            return Entry;
        }
        if (Diff > 0) break;

        Entry = Entry->Next;
    }

    if (!Unicode) ConsoleFreeHeap(SourceU.Buffer);
    return NULL;
}