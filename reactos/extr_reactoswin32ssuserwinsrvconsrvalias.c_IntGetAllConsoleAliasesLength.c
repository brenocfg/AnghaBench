#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_7__ {scalar_t__ Length; } ;
struct TYPE_6__ {scalar_t__ Length; } ;
struct TYPE_9__ {struct TYPE_9__* Next; TYPE_2__ Target; TYPE_1__ Source; } ;
struct TYPE_8__ {TYPE_4__* Data; } ;
typedef  TYPE_3__* PALIAS_HEADER ;
typedef  TYPE_4__* PALIAS_ENTRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */

__attribute__((used)) static UINT
IntGetAllConsoleAliasesLength(PALIAS_HEADER Header,
                              BOOLEAN IsUnicode)
{
    UINT Length = 0;
    PALIAS_ENTRY CurEntry = Header->Data;

    while (CurEntry)
    {
        Length += CurEntry->Source.Length;
        Length += CurEntry->Target.Length;
        Length += 2 * sizeof(WCHAR); // '=' and NULL-termination
        CurEntry = CurEntry->Next;
    }

    /*
     * Quick and dirty way of getting the number of bytes of the
     * corresponding ANSI string from the one in UNICODE.
     */
    if (!IsUnicode)
        Length /= sizeof(WCHAR);

    return Length;
}