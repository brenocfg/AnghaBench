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
typedef  int USHORT ;
typedef  size_t UCHAR ;
struct TYPE_3__ {scalar_t__ UniDefaultChar; scalar_t__* DBCSOffsets; } ;
typedef  scalar_t__* PUSHORT ;
typedef  TYPE_1__* PCPTABLEINFO ;

/* Variables and functions */

USHORT
NLS_RecordsCountForDBCSTable(PCPTABLEINFO CodePageTable, UCHAR LeadByte)
{
    PUSHORT LeadByteInfo = CodePageTable->DBCSOffsets;
    USHORT CodePageChar;
    USHORT Count = 0;

    for (CodePageChar = 0; CodePageChar <= 0xFF; CodePageChar++)
    {
        USHORT Info = LeadByteInfo[LeadByte];

        if (Info && LeadByteInfo[Info + CodePageChar] != CodePageTable->UniDefaultChar)
        {
            Count++;
        }
    }

    return Count;
}