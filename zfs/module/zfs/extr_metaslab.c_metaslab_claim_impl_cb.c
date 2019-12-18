#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {scalar_t__ mcca_error; int /*<<< orphan*/  mcca_txg; } ;
typedef  TYPE_1__ metaslab_claim_cb_arg_t ;

/* Variables and functions */
 scalar_t__ metaslab_claim_concrete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
metaslab_claim_impl_cb(uint64_t inner_offset, vdev_t *vd, uint64_t offset,
    uint64_t size, void *arg)
{
	metaslab_claim_cb_arg_t *mcca_arg = arg;

	if (mcca_arg->mcca_error == 0) {
		mcca_arg->mcca_error = metaslab_claim_concrete(vd, offset,
		    size, mcca_arg->mcca_txg);
	}
}