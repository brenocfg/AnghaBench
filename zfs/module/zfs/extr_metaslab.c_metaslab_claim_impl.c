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
struct TYPE_9__ {TYPE_1__* vdev_ops; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_10__ {scalar_t__ mcca_error; int /*<<< orphan*/  mcca_txg; } ;
typedef  TYPE_3__ metaslab_claim_cb_arg_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* vdev_op_remap ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int metaslab_claim_concrete (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_claim_impl_cb ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int
metaslab_claim_impl(vdev_t *vd, uint64_t offset, uint64_t size, uint64_t txg)
{
	if (vd->vdev_ops->vdev_op_remap != NULL) {
		metaslab_claim_cb_arg_t arg;

		/*
		 * Only zdb(1M) can claim on indirect vdevs.  This is used
		 * to detect leaks of mapped space (that are not accounted
		 * for in the obsolete counts, spacemap, or bpobj).
		 */
		ASSERT(!spa_writeable(vd->vdev_spa));
		arg.mcca_error = 0;
		arg.mcca_txg = txg;

		vd->vdev_ops->vdev_op_remap(vd, offset, size,
		    metaslab_claim_impl_cb, &arg);

		if (arg.mcca_error == 0) {
			arg.mcca_error = metaslab_claim_concrete(vd,
			    offset, size, txg);
		}
		return (arg.mcca_error);
	} else {
		return (metaslab_claim_concrete(vd, offset, size, txg));
	}
}