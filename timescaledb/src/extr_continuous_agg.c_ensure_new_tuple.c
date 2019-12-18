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
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  FormData_continuous_agg ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_copytuple (int /*<<< orphan*/ *) ; 

__attribute__((used)) static FormData_continuous_agg *
ensure_new_tuple(HeapTuple old_tuple, HeapTuple *new_tuple)
{
	if (*new_tuple == NULL)
		*new_tuple = heap_copytuple(old_tuple);

	return (FormData_continuous_agg *) GETSTRUCT(*new_tuple);
}