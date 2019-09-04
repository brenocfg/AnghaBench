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
typedef  int /*<<< orphan*/  tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  tree_iterate_cb ; 
 int /*<<< orphan*/  tree_reverse_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static unsigned
tree_iterate_reverse(tree_t *tree) {
	unsigned i;

	i = 0;
	tree_reverse_iter(tree, NULL, tree_iterate_cb, (void *)&i);

	return i;
}