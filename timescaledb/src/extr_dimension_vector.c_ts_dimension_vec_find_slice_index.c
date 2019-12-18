#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_7__ {int num_slices; TYPE_2__** slices; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_3__ DimensionVec ;

/* Variables and functions */

int
ts_dimension_vec_find_slice_index(DimensionVec *vec, int32 dimension_slice_id)
{
	int i;

	for (i = 0; i < vec->num_slices; i++)
		if (dimension_slice_id == vec->slices[i]->fd.id)
			return i;

	return -1;
}