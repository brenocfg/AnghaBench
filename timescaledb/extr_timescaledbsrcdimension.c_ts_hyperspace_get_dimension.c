#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {int num_dimensions; TYPE_2__* dimensions; } ;
typedef  scalar_t__ Index ;
typedef  TYPE_1__ Hyperspace ;
typedef  scalar_t__ DimensionType ;
typedef  TYPE_2__ Dimension ;

/* Variables and functions */
 scalar_t__ DIMENSION_TYPE_ANY ; 

Dimension *
ts_hyperspace_get_dimension(Hyperspace *hs, DimensionType type, Index n)
{
	int i;

	for (i = 0; i < hs->num_dimensions; i++)
	{
		if (type == DIMENSION_TYPE_ANY || hs->dimensions[i].type == type)
		{
			if (n == 0)
				return &hs->dimensions[i];
			n--;
		}
	}

	return NULL;
}