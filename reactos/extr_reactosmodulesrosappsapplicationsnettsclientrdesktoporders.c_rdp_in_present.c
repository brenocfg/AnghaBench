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
typedef  int uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int RDP_ORDER_SMALL ; 
 int RDP_ORDER_TINY ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_in_present(STREAM s, uint32 * present, uint8 flags, int size)
{
	uint8 bits;
	int i;

	if (flags & RDP_ORDER_SMALL)
	{
		size--;
	}

	if (flags & RDP_ORDER_TINY)
	{
		if (size < 2)
			size = 0;
		else
			size -= 2;
	}

	*present = 0;
	for (i = 0; i < size; i++)
	{
		in_uint8(s, bits);
		*present |= bits << (i * 8);
	}
}