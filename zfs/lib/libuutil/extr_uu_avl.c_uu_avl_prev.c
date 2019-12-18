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
struct TYPE_3__ {int /*<<< orphan*/  ua_tree; } ;
typedef  TYPE_1__ uu_avl_t ;

/* Variables and functions */
 void* AVL_PREV (int /*<<< orphan*/ *,void*) ; 

void *
uu_avl_prev(uu_avl_t *ap, void *node)
{
	return (AVL_PREV(&ap->ua_tree, node));
}