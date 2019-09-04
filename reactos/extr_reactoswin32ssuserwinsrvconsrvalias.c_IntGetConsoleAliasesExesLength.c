#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {scalar_t__ Length; } ;
struct TYPE_5__ {struct TYPE_5__* Next; TYPE_1__ ExeName; } ;
typedef  TYPE_2__* PALIAS_HEADER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */

__attribute__((used)) static UINT
IntGetConsoleAliasesExesLength(PALIAS_HEADER RootHeader,
                               BOOLEAN IsUnicode)
{
    UINT Length = 0;

    while (RootHeader)
    {
        Length += RootHeader->ExeName.Length + sizeof(WCHAR); // NULL-termination
        RootHeader = RootHeader->Next;
    }

    /*
     * Quick and dirty way of getting the number of bytes of the
     * corresponding ANSI string from the one in UNICODE.
     */
    if (!IsUnicode)
        Length /= sizeof(WCHAR);

    return Length;
}