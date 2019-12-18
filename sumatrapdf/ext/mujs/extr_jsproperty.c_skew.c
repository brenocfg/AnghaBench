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
struct TYPE_4__ {scalar_t__ level; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ js_Property ;

/* Variables and functions */

__attribute__((used)) static js_Property *skew(js_Property *node)
{
	if (node->left->level == node->level) {
		js_Property *temp = node;
		node = node->left;
		temp->left = node->right;
		node->right = temp;
	}
	return node;
}