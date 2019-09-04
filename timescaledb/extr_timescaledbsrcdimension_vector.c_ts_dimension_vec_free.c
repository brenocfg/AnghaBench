#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_slices; int /*<<< orphan*/ * slices; } ;
typedef  TYPE_1__ DimensionVec ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ts_dimension_slice_free (int /*<<< orphan*/ ) ; 

void
ts_dimension_vec_free(DimensionVec *vec)
{
	int i;

	for (i = 0; i < vec->num_slices; i++)
		ts_dimension_slice_free(vec->slices[i]);
	pfree(vec);
}