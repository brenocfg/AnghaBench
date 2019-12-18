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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_6__ {TYPE_3__* sm_dbuf; int /*<<< orphan*/  sm_phys; int /*<<< orphan*/  sm_blksz; int /*<<< orphan*/  sm_object; int /*<<< orphan*/  sm_os; } ;
typedef  TYPE_1__ space_map_t ;
struct TYPE_7__ {int /*<<< orphan*/  db_data; } ;

/* Variables and functions */
 int dmu_bonus_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__**) ; 
 int /*<<< orphan*/  dmu_object_size_from_db (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
space_map_open_impl(space_map_t *sm)
{
	int error;
	u_longlong_t blocks;

	error = dmu_bonus_hold(sm->sm_os, sm->sm_object, sm, &sm->sm_dbuf);
	if (error)
		return (error);

	dmu_object_size_from_db(sm->sm_dbuf, &sm->sm_blksz, &blocks);
	sm->sm_phys = sm->sm_dbuf->db_data;
	return (0);
}