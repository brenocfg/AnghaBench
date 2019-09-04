#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_t ;
struct TYPE_8__ {int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ rtree_node_elm_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* rtree_child_node_tryread (TYPE_1__*,int) ; 
 TYPE_1__* rtree_node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtree_node_valid (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static rtree_node_elm_t *
rtree_child_node_read(tsdn_t *tsdn, rtree_t *rtree, rtree_node_elm_t *elm,
    unsigned level, bool dependent) {
	rtree_node_elm_t *node;

	node = rtree_child_node_tryread(elm, dependent);
	if (!dependent && unlikely(!rtree_node_valid(node))) {
		node = rtree_node_init(tsdn, rtree, level + 1, &elm->child);
	}
	assert(!dependent || node != NULL);
	return node;
}