#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_ds_t ;
struct TYPE_7__ {scalar_t__ zgd_lr; scalar_t__ zgd_db; int /*<<< orphan*/ * zgd_private; } ;
typedef  TYPE_1__ zgd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  rl_object; } ;
typedef  TYPE_2__ rl_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  umem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ztest_object_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_range_unlock (TYPE_2__*) ; 

__attribute__((used)) static void
ztest_get_done(zgd_t *zgd, int error)
{
	ztest_ds_t *zd = zgd->zgd_private;
	uint64_t object = ((rl_t *)zgd->zgd_lr)->rl_object;

	if (zgd->zgd_db)
		dmu_buf_rele(zgd->zgd_db, zgd);

	ztest_range_unlock((rl_t *)zgd->zgd_lr);
	ztest_object_unlock(zd, object);

	umem_free(zgd, sizeof (*zgd));
}