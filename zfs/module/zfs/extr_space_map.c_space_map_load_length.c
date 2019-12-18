#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  sm_size; int /*<<< orphan*/  sm_start; } ;
typedef  TYPE_1__ space_map_t ;
struct TYPE_7__ {scalar_t__ smla_type; TYPE_1__* smla_sm; int /*<<< orphan*/ * smla_rt; } ;
typedef  TYPE_2__ space_map_load_arg_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  scalar_t__ maptype_t ;

/* Variables and functions */
 scalar_t__ SM_FREE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int space_map_iterate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  space_map_load_callback ; 

int
space_map_load_length(space_map_t *sm, range_tree_t *rt, maptype_t maptype,
    uint64_t length)
{
	space_map_load_arg_t smla;

	VERIFY0(range_tree_space(rt));

	if (maptype == SM_FREE)
		range_tree_add(rt, sm->sm_start, sm->sm_size);

	smla.smla_rt = rt;
	smla.smla_sm = sm;
	smla.smla_type = maptype;
	int err = space_map_iterate(sm, length,
	    space_map_load_callback, &smla);

	if (err != 0)
		range_tree_vacate(rt, NULL, NULL);

	return (err);
}