#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_5__ {int /*<<< orphan*/  init_lock; } ;
typedef  TYPE_1__ rtree_t ;
typedef  int /*<<< orphan*/  rtree_node_elm_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_ptr_not_null (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtree_node_alloc_orig (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 TYPE_1__ test_rtree ; 

__attribute__((used)) static rtree_node_elm_t *
rtree_node_alloc_intercept(tsdn_t *tsdn, rtree_t *rtree, size_t nelms) {
	rtree_node_elm_t *node;

	if (rtree != &test_rtree) {
		return rtree_node_alloc_orig(tsdn, rtree, nelms);
	}

	malloc_mutex_unlock(tsdn, &rtree->init_lock);
	node = (rtree_node_elm_t *)calloc(nelms, sizeof(rtree_node_elm_t));
	assert_ptr_not_null(node, "Unexpected calloc() failure");
	malloc_mutex_lock(tsdn, &rtree->init_lock);

	return node;
}