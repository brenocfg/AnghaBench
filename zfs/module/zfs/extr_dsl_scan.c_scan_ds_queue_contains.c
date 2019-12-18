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
struct TYPE_6__ {int /*<<< orphan*/  sds_txg; int /*<<< orphan*/  sds_dsobj; } ;
typedef  TYPE_1__ scan_ds_t ;
struct TYPE_7__ {int /*<<< orphan*/  scn_queue; } ;
typedef  TYPE_2__ dsl_scan_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
scan_ds_queue_contains(dsl_scan_t *scn, uint64_t dsobj, uint64_t *txg)
{
	scan_ds_t srch, *sds;

	srch.sds_dsobj = dsobj;
	sds = avl_find(&scn->scn_queue, &srch, NULL);
	if (sds != NULL && txg != NULL)
		*txg = sds->sds_txg;
	return (sds != NULL);
}