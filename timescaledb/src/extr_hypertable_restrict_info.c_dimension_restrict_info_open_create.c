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
struct TYPE_5__ {int /*<<< orphan*/ * dimension; } ;
struct TYPE_6__ {void* upper_strategy; void* lower_strategy; TYPE_1__ base; } ;
typedef  TYPE_2__ DimensionRestrictInfoOpen ;
typedef  int /*<<< orphan*/  Dimension ;

/* Variables and functions */
 void* InvalidStrategy ; 
 TYPE_2__* palloc (int) ; 

__attribute__((used)) static DimensionRestrictInfoOpen *
dimension_restrict_info_open_create(Dimension *d)
{
	DimensionRestrictInfoOpen *new = palloc(sizeof(DimensionRestrictInfoOpen));

	new->base.dimension = d;
	new->lower_strategy = InvalidStrategy;
	new->upper_strategy = InvalidStrategy;
	return new;
}