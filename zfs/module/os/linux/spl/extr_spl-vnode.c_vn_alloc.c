#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ v_type; int /*<<< orphan*/ * v_file; } ;
typedef  TYPE_1__ vnode_t ;

/* Variables and functions */
 TYPE_1__* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vn_cache ; 

vnode_t *
vn_alloc(int flag)
{
	vnode_t *vp;

	vp = kmem_cache_alloc(vn_cache, flag);
	if (vp != NULL) {
		vp->v_file = NULL;
		vp->v_type = 0;
	}

	return (vp);
}