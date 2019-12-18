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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_t ;
struct TYPE_4__ {int /*<<< orphan*/  child; } ;
typedef  TYPE_1__ rtree_node_elm_t ;
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * rtree_child_leaf_tryread (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * rtree_leaf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtree_leaf_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static rtree_leaf_elm_t *
rtree_child_leaf_read(tsdn_t *tsdn, rtree_t *rtree, rtree_node_elm_t *elm,
    unsigned level, bool dependent) {
	rtree_leaf_elm_t *leaf;

	leaf = rtree_child_leaf_tryread(elm, dependent);
	if (!dependent && unlikely(!rtree_leaf_valid(leaf))) {
		leaf = rtree_leaf_init(tsdn, rtree, &elm->child);
	}
	assert(!dependent || leaf != NULL);
	return leaf;
}