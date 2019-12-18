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
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_8__ {int /*<<< orphan*/ * Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_10__ {struct TYPE_10__* Next; int /*<<< orphan*/  ExeName; } ;
struct TYPE_9__ {TYPE_3__* Aliases; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_2__* PCONSRV_CONSOLE ;
typedef  TYPE_3__* PALIAS_HEADER ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleFreeHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConvertInputAnsiToUnicode (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlCompareUnicodeString (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static PALIAS_HEADER
IntFindAliasHeader(PCONSRV_CONSOLE Console,
                   PVOID    ExeName,
                   USHORT   ExeLength,
                   BOOLEAN  UnicodeExe)
{
    UNICODE_STRING ExeNameU;

    PALIAS_HEADER RootHeader = Console->Aliases;
    INT Diff;

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

    while (RootHeader)
    {
        Diff = RtlCompareUnicodeString(&RootHeader->ExeName, &ExeNameU, TRUE);
        if (!Diff)
        {
            if (!UnicodeExe) ConsoleFreeHeap(ExeNameU.Buffer);
            return RootHeader;
        }
        if (Diff > 0) break;

        RootHeader = RootHeader->Next;
    }

    if (!UnicodeExe) ConsoleFreeHeap(ExeNameU.Buffer);
    return NULL;
}