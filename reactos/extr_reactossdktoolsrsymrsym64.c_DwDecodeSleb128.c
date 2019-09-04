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

/* Variables and functions */

unsigned long
DwDecodeSleb128(long *pResult, char *pc)
{
	long lResult = 0;
	unsigned long ulShift = 0;
	unsigned char current;
	unsigned long ulSize = 0;

	do
	{
		current = pc[ulSize];
		ulSize++;
		lResult |= (current & 0x7f) << ulShift;
		ulShift += 7;
	}
	while (current & 0x80);

	if (current & 0x40)
		lResult |= - (1 << (ulShift));

    *pResult = lResult;

	return ulSize;
}