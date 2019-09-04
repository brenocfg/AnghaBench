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
typedef  scalar_t__ Oid ;

/* Variables and functions */

bool
ts_function_types_equal(Oid left[], Oid right[], int nargs)
{
	int arg_index;

	for (arg_index = 0; arg_index < nargs; arg_index++)
	{
		if (left[arg_index] != right[arg_index])
			return false;
	}
	return true;
}