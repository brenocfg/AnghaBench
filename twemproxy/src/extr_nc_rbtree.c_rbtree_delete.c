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
typedef  scalar_t__ uint8_t ;
struct rbtree {struct rbnode* sentinel; struct rbnode* root; } ;
struct rbnode {struct rbnode* parent; struct rbnode* left; struct rbnode* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbtree_black (struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_copy_color (struct rbnode*,struct rbnode*) ; 
 scalar_t__ rbtree_is_black (struct rbnode*) ; 
 scalar_t__ rbtree_is_red (struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_left_rotate (struct rbnode**,struct rbnode*,struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_node_init (struct rbnode*) ; 
 struct rbnode* rbtree_node_min (struct rbnode*,struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_red (struct rbnode*) ; 
 int /*<<< orphan*/  rbtree_right_rotate (struct rbnode**,struct rbnode*,struct rbnode*) ; 

void
rbtree_delete(struct rbtree *tree, struct rbnode *node)
{
    struct rbnode **root = &tree->root;
    struct rbnode *sentinel = tree->sentinel;
    struct rbnode *subst, *temp, *w;
    uint8_t red;

    /* a binary tree delete */

    if (node->left == sentinel) {
        temp = node->right;
        subst = node;
    } else if (node->right == sentinel) {
        temp = node->left;
        subst = node;
    } else {
        subst = rbtree_node_min(node->right, sentinel);
        temp = subst->right;
    }

    if (subst == *root) {
        *root = temp;
        rbtree_black(temp);

        rbtree_node_init(node);

        return;
    }

    red = rbtree_is_red(subst);

    if (subst == subst->parent->left) {
        subst->parent->left = temp;
    } else {
        subst->parent->right = temp;
    }

    if (subst == node) {
        temp->parent = subst->parent;
    } else {

        if (subst->parent == node) {
            temp->parent = subst;
        } else {
            temp->parent = subst->parent;
        }

        subst->left = node->left;
        subst->right = node->right;
        subst->parent = node->parent;
        rbtree_copy_color(subst, node);

        if (node == *root) {
            *root = subst;
        } else {
            if (node == node->parent->left) {
                node->parent->left = subst;
            } else {
                node->parent->right = subst;
            }
        }

        if (subst->left != sentinel) {
            subst->left->parent = subst;
        }

        if (subst->right != sentinel) {
            subst->right->parent = subst;
        }
    }

    rbtree_node_init(node);

    if (red) {
        return;
    }

    /* a delete fixup */

    while (temp != *root && rbtree_is_black(temp)) {

        if (temp == temp->parent->left) {
            w = temp->parent->right;

            if (rbtree_is_red(w)) {
                rbtree_black(w);
                rbtree_red(temp->parent);
                rbtree_left_rotate(root, sentinel, temp->parent);
                w = temp->parent->right;
            }

            if (rbtree_is_black(w->left) && rbtree_is_black(w->right)) {
                rbtree_red(w);
                temp = temp->parent;
            } else {
                if (rbtree_is_black(w->right)) {
                    rbtree_black(w->left);
                    rbtree_red(w);
                    rbtree_right_rotate(root, sentinel, w);
                    w = temp->parent->right;
                }

                rbtree_copy_color(w, temp->parent);
                rbtree_black(temp->parent);
                rbtree_black(w->right);
                rbtree_left_rotate(root, sentinel, temp->parent);
                temp = *root;
            }

        } else {
            w = temp->parent->left;

            if (rbtree_is_red(w)) {
                rbtree_black(w);
                rbtree_red(temp->parent);
                rbtree_right_rotate(root, sentinel, temp->parent);
                w = temp->parent->left;
            }

            if (rbtree_is_black(w->left) && rbtree_is_black(w->right)) {
                rbtree_red(w);
                temp = temp->parent;
            } else {
                if (rbtree_is_black(w->left)) {
                    rbtree_black(w->right);
                    rbtree_red(w);
                    rbtree_left_rotate(root, sentinel, w);
                    w = temp->parent->left;
                }

                rbtree_copy_color(w, temp->parent);
                rbtree_black(temp->parent);
                rbtree_black(w->left);
                rbtree_right_rotate(root, sentinel, temp->parent);
                temp = *root;
            }
        }
    }

    rbtree_black(temp);
}