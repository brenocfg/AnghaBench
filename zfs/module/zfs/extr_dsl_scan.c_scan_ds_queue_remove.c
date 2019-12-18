#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  sds_dsobj; } ;
typedef  TYPE_1__ scan_ds_t ;
struct TYPE_9__ {int /*<<< orphan*/  scn_queue; } ;
typedef  TYPE_2__ dsl_scan_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

__attribute__((used)) static void
scan_ds_queue_remove(dsl_scan_t *scn, uint64_t dsobj)
{
	scan_ds_t srch, *sds;

	srch.sds_dsobj = dsobj;

	sds = avl_find(&scn->scn_queue, &srch, NULL);
	VERIFY(sds != NULL);
	avl_remove(&scn->scn_queue, sds);
	kmem_free(sds, sizeof (*sds));
}