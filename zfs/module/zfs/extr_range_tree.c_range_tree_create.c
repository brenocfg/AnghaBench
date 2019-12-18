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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  range_tree_ops_t ;
typedef  int /*<<< orphan*/  range_seg_type_t ;

/* Variables and functions */
 int /*<<< orphan*/ * range_tree_create_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

range_tree_t *
range_tree_create(range_tree_ops_t *ops, range_seg_type_t type,
    void *arg, uint64_t start, uint64_t shift)
{
	return (range_tree_create_impl(ops, type, arg, start, shift, NULL, 0));
}