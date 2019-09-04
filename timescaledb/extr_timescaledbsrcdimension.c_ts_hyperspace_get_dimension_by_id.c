#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/  dimensions; } ;
typedef  TYPE_2__ Hyperspace ;
typedef  TYPE_3__ Dimension ;

/* Variables and functions */
 TYPE_3__* bsearch (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_dimension_id ; 

Dimension *
ts_hyperspace_get_dimension_by_id(Hyperspace *hs, int32 id)
{
	Dimension dim = {
		.fd.id = id,
	};

	return bsearch(&dim, hs->dimensions, hs->num_dimensions, sizeof(Dimension), cmp_dimension_id);
}