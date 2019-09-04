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
struct rbnode {unsigned long long key; int /*<<< orphan*/ * data; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; } ;

/* Variables and functions */

void
rbtree_node_init(struct rbnode *node)
{
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->key = 0ULL;
    node->data = NULL;
    /* color is left uninitialized */
}