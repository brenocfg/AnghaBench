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
struct TYPE_6__ {int /*<<< orphan*/  strategy; TYPE_1__ base; int /*<<< orphan*/  partitions; } ;
typedef  TYPE_2__ DimensionRestrictInfoClosed ;
typedef  int /*<<< orphan*/  Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidStrategy ; 
 int /*<<< orphan*/  NIL ; 
 TYPE_2__* palloc (int) ; 

__attribute__((used)) static DimensionRestrictInfoClosed *
dimension_restrict_info_closed_create(Dimension *d)
{
	DimensionRestrictInfoClosed *new = palloc(sizeof(DimensionRestrictInfoClosed));

	new->partitions = NIL;
	new->base.dimension = d;
	new->strategy = InvalidStrategy;
	return new;
}