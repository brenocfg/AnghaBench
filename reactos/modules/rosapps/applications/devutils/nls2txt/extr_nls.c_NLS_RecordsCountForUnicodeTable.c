#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PCPTABLEINFO ;

/* Variables and functions */
 int /*<<< orphan*/  NLS_IsDefaultCharForUnicode (int /*<<< orphan*/ ,int) ; 

USHORT
NLS_RecordsCountForUnicodeTable(PCPTABLEINFO CodePageTable)
{
    ULONG UnicodeChar;
    USHORT Count = 0;

    for (UnicodeChar = 0; UnicodeChar <= 0xFFFF; UnicodeChar++)
    {
        if (!NLS_IsDefaultCharForUnicode(CodePageTable, UnicodeChar))
            Count++;
    }

    return Count;
}