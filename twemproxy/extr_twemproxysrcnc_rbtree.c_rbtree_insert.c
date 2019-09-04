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
struct rbnode {scalar_t__ key; struct rbnode* parent; struct rbnode* left; struct rbnode* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbtree_black (struct rbnode*) ; 
 scalar_t__ rbtree_is_red (struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_left_rotate (struct rbnode**,struct rbnode*,struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_red (struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_right_rotate (struct rbnode**,struct rbnode*,struct rbnode*) ; 

void
rbtree_insert(struct rbtree *tree, struct rbnode *node)
{
    struct rbnode **root = &tree->root;
    struct rbnode *sentinel = tree->sentinel;
    struct rbnode *temp, **p;

    /* empty tree */

    if (*root == sentinel) {
        node->parent = NULL;
        node->left = sentinel;
        node->right = sentinel;
        rbtree_black(node);
        *root = node;
        return;
    }

    /* a binary tree insert */

    temp = *root;
    for (;;) {

        p = (node->key < temp->key) ? &temp->left : &temp->right;
        if (*p == sentinel) {
            break;
        }
        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    rbtree_red(node);

    /* re-balance tree */

    while (node != *root && rbtree_is_red(node->parent)) {

        if (node->parent == node->parent->parent->left) {
            temp = node->parent->parent->right;

            if (rbtree_is_red(temp)) {
                rbtree_black(node->parent);
                rbtree_black(temp);
                rbtree_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rbtree_left_rotate(root, sentinel, node);
                }

                rbtree_black(node->parent);
                rbtree_red(node->parent->parent);
                rbtree_right_rotate(root, sentinel, node->parent->parent);
            }
        } else {
            temp = node->parent->parent->left;

            if (rbtree_is_red(temp)) {
                rbtree_black(node->parent);
                rbtree_black(temp);
                rbtree_red(node->parent->parent);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rbtree_right_rotate(root, sentinel, node);
                }

                rbtree_black(node->parent);
                rbtree_red(node->parent->parent);
                rbtree_left_rotate(root, sentinel, node->parent->parent);
            }
        }
    }

    rbtree_black(*root);
}