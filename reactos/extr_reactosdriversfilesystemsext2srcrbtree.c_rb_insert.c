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
struct rb_root {struct rb_node* rb_node; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_insert_color (struct rb_node*,struct rb_root*) ; 
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 

void rb_insert(struct rb_root *root, struct rb_node *node,
         int (*cmp)(struct rb_node *, struct rb_node *))
{
    struct rb_node **new = &(root->rb_node), *parent = NULL;

    /* Figure out where to put new node */
    while (*new) {
        int result = cmp(node, *new);

        parent = *new;
        if (result < 0)
            new = &((*new)->rb_left);
        else if (result > 0)
            new = &((*new)->rb_right);
        else
            return;

    }

    /* Add new node and rebalance tree. */
    rb_link_node(node, parent, new);
    rb_insert_color(node, root);
}