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
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_4__ {int /*<<< orphan*/  capacity; } ;
typedef  TYPE_1__ Hypercube ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERCUBE_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc0 (int /*<<< orphan*/ ) ; 

Hypercube *
ts_hypercube_alloc(int16 num_dimensions)
{
	Hypercube *hc = palloc0(HYPERCUBE_SIZE(num_dimensions));

	hc->capacity = num_dimensions;
	return hc;
}