#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  rtree_t ;
typedef  int /*<<< orphan*/  rtree_leaf_elm_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 int /*<<< orphan*/  b0get () ; 
 scalar_t__ base_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtree_leaf_elm_t *
rtree_leaf_alloc_impl(tsdn_t *tsdn, rtree_t *rtree, size_t nelms) {
	return (rtree_leaf_elm_t *)base_alloc(tsdn, b0get(), nelms *
	    sizeof(rtree_leaf_elm_t), CACHELINE);
}