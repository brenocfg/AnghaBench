#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* avl_root; } ;
typedef  TYPE_1__ avl_tree_t ;
struct TYPE_14__ {struct TYPE_14__** avl_child; } ;
typedef  TYPE_2__ avl_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVL_SETBALANCE (TYPE_2__*,int) ; 
 int /*<<< orphan*/  AVL_SETCHILD (TYPE_2__*,int) ; 
 int /*<<< orphan*/  AVL_SETPARENT (TYPE_2__*,TYPE_2__*) ; 
 int AVL_XBALANCE (TYPE_2__*) ; 
 int AVL_XCHILD (TYPE_2__*) ; 
 TYPE_2__* AVL_XPARENT (TYPE_2__*) ; 

__attribute__((used)) static int
avl_rotation(avl_tree_t *tree, avl_node_t *node, int balance)
{
	int left = !(balance < 0);	/* when balance = -2, left will be 0 */
	int right = 1 - left;
	int left_heavy = balance >> 1;
	int right_heavy = -left_heavy;
	avl_node_t *parent = AVL_XPARENT(node);
	avl_node_t *child = node->avl_child[left];
	avl_node_t *cright;
	avl_node_t *gchild;
	avl_node_t *gright;
	avl_node_t *gleft;
	int which_child = AVL_XCHILD(node);
	int child_bal = AVL_XBALANCE(child);

	/* BEGIN CSTYLED */
	/*
	 * case 1 : node is overly left heavy, the left child is balanced or
	 * also left heavy. This requires the following rotation.
	 *
	 *                   (node bal:-2)
	 *                    /           \
	 *                   /             \
	 *              (child bal:0 or -1)
	 *              /    \
	 *             /      \
	 *                     cright
	 *
	 * becomes:
	 *
	 *              (child bal:1 or 0)
	 *              /        \
	 *             /          \
	 *                        (node bal:-1 or 0)
	 *                         /     \
	 *                        /       \
	 *                     cright
	 *
	 * we detect this situation by noting that child's balance is not
	 * right_heavy.
	 */
	/* END CSTYLED */
	if (child_bal != right_heavy) {

		/*
		 * compute new balance of nodes
		 *
		 * If child used to be left heavy (now balanced) we reduced
		 * the height of this sub-tree -- used in "return...;" below
		 */
		child_bal += right_heavy; /* adjust towards right */

		/*
		 * move "cright" to be node's left child
		 */
		cright = child->avl_child[right];
		node->avl_child[left] = cright;
		if (cright != NULL) {
			AVL_SETPARENT(cright, node);
			AVL_SETCHILD(cright, left);
		}

		/*
		 * move node to be child's right child
		 */
		child->avl_child[right] = node;
		AVL_SETBALANCE(node, -child_bal);
		AVL_SETCHILD(node, right);
		AVL_SETPARENT(node, child);

		/*
		 * update the pointer into this subtree
		 */
		AVL_SETBALANCE(child, child_bal);
		AVL_SETCHILD(child, which_child);
		AVL_SETPARENT(child, parent);
		if (parent != NULL)
			parent->avl_child[which_child] = child;
		else
			tree->avl_root = child;

		return (child_bal == 0);
	}

	/* BEGIN CSTYLED */
	/*
	 * case 2 : When node is left heavy, but child is right heavy we use
	 * a different rotation.
	 *
	 *                   (node b:-2)
	 *                    /   \
	 *                   /     \
	 *                  /       \
	 *             (child b:+1)
	 *              /     \
	 *             /       \
	 *                   (gchild b: != 0)
	 *                     /  \
	 *                    /    \
	 *                 gleft   gright
	 *
	 * becomes:
	 *
	 *              (gchild b:0)
	 *              /       \
	 *             /         \
	 *            /           \
	 *        (child b:?)   (node b:?)
	 *         /  \          /   \
	 *        /    \        /     \
	 *            gleft   gright
	 *
	 * computing the new balances is more complicated. As an example:
	 *	 if gchild was right_heavy, then child is now left heavy
	 *		else it is balanced
	 */
	/* END CSTYLED */
	gchild = child->avl_child[right];
	gleft = gchild->avl_child[left];
	gright = gchild->avl_child[right];

	/*
	 * move gright to left child of node and
	 *
	 * move gleft to right child of node
	 */
	node->avl_child[left] = gright;
	if (gright != NULL) {
		AVL_SETPARENT(gright, node);
		AVL_SETCHILD(gright, left);
	}

	child->avl_child[right] = gleft;
	if (gleft != NULL) {
		AVL_SETPARENT(gleft, child);
		AVL_SETCHILD(gleft, right);
	}

	/*
	 * move child to left child of gchild and
	 *
	 * move node to right child of gchild and
	 *
	 * fixup parent of all this to point to gchild
	 */
	balance = AVL_XBALANCE(gchild);
	gchild->avl_child[left] = child;
	AVL_SETBALANCE(child, (balance == right_heavy ? left_heavy : 0));
	AVL_SETPARENT(child, gchild);
	AVL_SETCHILD(child, left);

	gchild->avl_child[right] = node;
	AVL_SETBALANCE(node, (balance == left_heavy ? right_heavy : 0));
	AVL_SETPARENT(node, gchild);
	AVL_SETCHILD(node, right);

	AVL_SETBALANCE(gchild, 0);
	AVL_SETPARENT(gchild, parent);
	AVL_SETCHILD(gchild, which_child);
	if (parent != NULL)
		parent->avl_child[which_child] = gchild;
	else
		tree->avl_root = gchild;

	return (1);	/* the new tree is always shorter */
}