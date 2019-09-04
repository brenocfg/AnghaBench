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
struct rb_node {struct rb_node* rb_left; struct rb_node* rb_right; } ;

/* Variables and functions */
 struct rb_node* rb_parent (struct rb_node*) ; 

struct rb_node *rb_prev(struct rb_node *node)
{
    struct rb_node *parent;

    /* If we have a left-hand child, go down and then right as far
       as we can. */
    if (node->rb_left) {
        node = node->rb_left;
        while (node->rb_right)
            node=node->rb_right;
        return node;
    }

    /* No left-hand children. Go up till we find an ancestor which
       is a right-hand child of its parent */
    while ((parent = rb_parent(node)) && node == parent->rb_left)
        node = parent;

    return parent;
}