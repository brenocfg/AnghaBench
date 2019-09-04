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
typedef  size_t USHORT ;
struct TYPE_4__ {size_t DefaultChar; int /*<<< orphan*/  WideCharTable; } ;
typedef  size_t* PUSHORT ;
typedef  size_t* PUCHAR ;
typedef  TYPE_1__* PCPTABLEINFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NLS_IsDBCSCodePage (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
NLS_IsDefaultCharForUnicode(PCPTABLEINFO CodePageTable, USHORT Char)
{
    USHORT CodePageChar;

    if (NLS_IsDBCSCodePage(CodePageTable))
    {
        PUSHORT MultiByteTable = (PUSHORT)CodePageTable->WideCharTable;
        CodePageChar = MultiByteTable[Char];
    }
    else
    {
        PUCHAR SingleByteTable = (PUCHAR)CodePageTable->WideCharTable;
        CodePageChar = SingleByteTable[Char];
    }

    if (CodePageChar != CodePageTable->DefaultChar)
        return FALSE;

    return TRUE;
}