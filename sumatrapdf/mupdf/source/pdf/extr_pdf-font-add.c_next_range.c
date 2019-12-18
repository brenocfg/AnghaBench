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

__attribute__((used)) static int next_range(int *table, int size, int k)
{
	int n;
	for (n = 1; k + n < size; ++n)
	{
		if ((k & 0xFF00) != ((k+n) & 0xFF00)) /* high byte changes */
			break;
		if (table[k] + n != table[k+n])
			break;
	}
	return n;
}