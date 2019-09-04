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
struct rbnode {struct rbnode* parent; struct rbnode* right; struct rbnode* left; } ;

/* Variables and functions */

__attribute__((used)) static void
rbtree_right_rotate(struct rbnode **root, struct rbnode *sentinel,
                    struct rbnode *node)
{
    struct rbnode *temp;

    temp = node->left;
    node->left = temp->right;

    if (temp->right != sentinel) {
        temp->right->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root) {
        *root = temp;
    } else if (node == node->parent->right) {
        node->parent->right = temp;
    } else {
        node->parent->left = temp;
    }

    temp->right = node;
    node->parent = temp;
}