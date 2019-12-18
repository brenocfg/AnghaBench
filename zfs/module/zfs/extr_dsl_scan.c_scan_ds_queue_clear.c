#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scan_ds_t ;
struct TYPE_3__ {int /*<<< orphan*/  scn_queue; } ;
typedef  TYPE_1__ dsl_scan_t ;

/* Variables and functions */
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
scan_ds_queue_clear(dsl_scan_t *scn)
{
	void *cookie = NULL;
	scan_ds_t *sds;
	while ((sds = avl_destroy_nodes(&scn->scn_queue, &cookie)) != NULL) {
		kmem_free(sds, sizeof (*sds));
	}
}