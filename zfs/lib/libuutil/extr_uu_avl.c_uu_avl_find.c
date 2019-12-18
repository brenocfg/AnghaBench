#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ua_debug; int /*<<< orphan*/  ua_tree; TYPE_1__* ua_pool; } ;
typedef  TYPE_2__ uu_avl_t ;
typedef  int /*<<< orphan*/  uu_avl_index_t ;
struct uu_avl_node_compare_info {void* ac_found; void* ac_right; void* ac_private; int /*<<< orphan*/  ac_compare; } ;
struct TYPE_5__ {int /*<<< orphan*/  uap_cmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_ENCODE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* avl_find (int /*<<< orphan*/ *,struct uu_avl_node_compare_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_panic (char*) ; 

void *
uu_avl_find(uu_avl_t *ap, void *elem, void *private, uu_avl_index_t *out)
{
	struct uu_avl_node_compare_info info;
	void *result;

	info.ac_compare = ap->ua_pool->uap_cmp;
	info.ac_private = private;
	info.ac_right = elem;
	info.ac_found = NULL;

	result = avl_find(&ap->ua_tree, &info, out);
	if (out != NULL)
		*out = INDEX_ENCODE(ap, *out);

	if (ap->ua_debug && result != NULL)
		uu_panic("uu_avl_find: internal error: avl_find succeeded\n");

	return (info.ac_found);
}