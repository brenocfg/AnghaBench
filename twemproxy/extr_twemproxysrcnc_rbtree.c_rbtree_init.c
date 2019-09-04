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
struct rbtree {struct rbnode* sentinel; struct rbnode* root; } ;
struct rbnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbtree_black (struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_node_init (struct rbnode*) ; 

void
rbtree_init(struct rbtree *tree, struct rbnode *node)
{
    rbtree_node_init(node);
    rbtree_black(node);
    tree->root = node;
    tree->sentinel = node;
}