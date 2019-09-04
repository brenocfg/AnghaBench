#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__ fd; } ;
struct TYPE_7__ {int num_dimensions; TYPE_3__* dimensions; } ;
typedef  TYPE_2__ Hyperspace ;
typedef  scalar_t__ DimensionType ;
typedef  TYPE_3__ Dimension ;

/* Variables and functions */
 scalar_t__ DIMENSION_TYPE_ANY ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ *,char const*) ; 

Dimension *
ts_hyperspace_get_dimension_by_name(Hyperspace *hs, DimensionType type, const char *name)
{
	int i;

	for (i = 0; i < hs->num_dimensions; i++)
	{
		Dimension *dim = &hs->dimensions[i];

		if ((type == DIMENSION_TYPE_ANY || dim->type == type) &&
			namestrcmp(&dim->fd.column_name, name) == 0)
			return dim;
	}

	return NULL;
}