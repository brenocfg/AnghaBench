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
struct TYPE_4__ {scalar_t__ key; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */

__attribute__((used)) static int
node_cmp(const node_t *a, const node_t *b) {
	int ret;

	ret = (a->key > b->key) - (a->key < b->key);
	if (ret == 0) {
		/*
		 * Duplicates are not allowed in the heap, so force an
		 * arbitrary ordering for non-identical items with equal keys.
		 */
		ret = (((uintptr_t)a) > ((uintptr_t)b))
		    - (((uintptr_t)a) < ((uintptr_t)b));
	}
	return ret;
}