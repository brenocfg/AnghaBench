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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int FSE_CTABLE_SIZE_U32 (unsigned int,unsigned int) ; 
 unsigned int FSE_MAX_TABLELOG ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t FSE_sizeof_CTable(unsigned maxSymbolValue, unsigned tableLog)
{
	if (tableLog > FSE_MAX_TABLELOG)
		return ERROR(tableLog_tooLarge);
	return FSE_CTABLE_SIZE_U32(tableLog, maxSymbolValue) * sizeof(U32);
}