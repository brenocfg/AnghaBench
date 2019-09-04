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
typedef  int USHORT ;
struct TYPE_4__ {int* MultiByteTable; int UniDefaultChar; } ;
typedef  int* PUSHORT ;
typedef  TYPE_1__* PCPTABLEINFO ;

/* Variables and functions */
 scalar_t__ NLS_IsGlyphTablePresent (TYPE_1__*) ; 

USHORT
NLS_RecordsCountForGlyphTable(PCPTABLEINFO CodePageTable)
{
    USHORT Count = 0;

    if (NLS_IsGlyphTablePresent(CodePageTable))
    {
        PUSHORT GlyphTable = CodePageTable->MultiByteTable + 256 + 1;
        USHORT CodePageChar;

        for (CodePageChar = 0; CodePageChar <= 0xFF; CodePageChar++)
        {
            USHORT Char = GlyphTable[CodePageChar];

            if (Char != CodePageTable->UniDefaultChar)
                Count++;
        }
    }

    return Count;
}