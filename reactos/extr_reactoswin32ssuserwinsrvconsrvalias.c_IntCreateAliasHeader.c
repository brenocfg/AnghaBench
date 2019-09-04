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
typedef  scalar_t__ USHORT ;
struct TYPE_7__ {int /*<<< orphan*/ * Buffer; scalar_t__ Length; scalar_t__ MaximumLength; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_9__ {scalar_t__ MaximumLength; scalar_t__ Length; scalar_t__ Buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Next; int /*<<< orphan*/ * Data; TYPE_3__ ExeName; } ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;
typedef  TYPE_2__* PALIAS_HEADER ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ALIAS_HEADER ;

/* Variables and functions */
 TYPE_2__* ConsoleAllocHeap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ConsoleFreeHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConvertInputAnsiToUnicode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  RtlCopyUnicodeString (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static PALIAS_HEADER
IntCreateAliasHeader(PCONSRV_CONSOLE Console,
                     PVOID    ExeName,
                     USHORT   ExeLength,
                     BOOLEAN  UnicodeExe)
{
    UNICODE_STRING ExeNameU;

    PALIAS_HEADER Entry;

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

    Entry = ConsoleAllocHeap(0, sizeof(ALIAS_HEADER) + ExeNameU.Length);
    if (!Entry)
    {
        if (!UnicodeExe) ConsoleFreeHeap(ExeNameU.Buffer);
        return Entry;
    }

    Entry->ExeName.Buffer = (PWSTR)(Entry + 1);
    Entry->ExeName.Length = 0;
    Entry->ExeName.MaximumLength = ExeNameU.Length;
    RtlCopyUnicodeString(&Entry->ExeName, &ExeNameU);

    Entry->Data = NULL;
    Entry->Next = NULL;

    if (!UnicodeExe) ConsoleFreeHeap(ExeNameU.Buffer);
    return Entry;
}