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
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 

ULONG
FFSLog2(
	ULONG Value)
{
	ULONG Order = 0;

    PAGED_CODE();

	ASSERT(Value > 0);

	while (Value)
	{
		Order++;
		Value >>= 1;
	}

	return (Order - 1);
}