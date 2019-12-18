#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* v_file; int /*<<< orphan*/  v_gfp_mask; int /*<<< orphan*/  f_mapping; } ;
typedef  TYPE_1__ vnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int filp_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_free (TYPE_1__*) ; 

int
vn_close(vnode_t *vp, int flags, int x1, int x2, void *x3, void *x4)
{
	int rc;

	ASSERT(vp);
	ASSERT(vp->v_file);

	mapping_set_gfp_mask(vp->v_file->f_mapping, vp->v_gfp_mask);
	rc = filp_close(vp->v_file, 0);
	vn_free(vp);

	return (-rc);
}