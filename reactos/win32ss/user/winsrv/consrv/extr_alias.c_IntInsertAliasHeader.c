#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/  ExeName; } ;
typedef  TYPE_1__* PALIAS_HEADER ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ RtlCompareUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID
IntInsertAliasHeader(PALIAS_HEADER* RootHeader,
                     PALIAS_HEADER  NewHeader)
{
    PALIAS_HEADER CurrentHeader;
    PALIAS_HEADER *LastLink = RootHeader;
    INT Diff;

    while ((CurrentHeader = *LastLink) != NULL)
    {
        Diff = RtlCompareUnicodeString(&NewHeader->ExeName, &CurrentHeader->ExeName, TRUE);
        if (Diff < 0) break;

        LastLink = &CurrentHeader->Next;
    }

    *LastLink = NewHeader;
    NewHeader->Next = CurrentHeader;
}