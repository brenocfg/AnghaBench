#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree {scalar_t__ next_node; TYPE_1__* nodes; } ;
struct TYPE_2__ {int length; int value; int is_value; } ;

/* Variables and functions */
 scalar_t__ MAX_TREE_NODES ; 
 int TREE_FAST_BITS ; 

__attribute__((used)) static bool tree_add_value(struct tree *tree, int key, int bits, int value)
{
    int rkey = 0, i;
    for (i = 0; i < bits; i++)
        rkey = (rkey << 1) | ((key >> i) & 1);

    if (bits <= TREE_FAST_BITS) {
        if (tree->nodes[rkey].length)
            return false;
        tree->nodes[rkey].length = bits;
        tree->nodes[rkey].value = value;
        tree->nodes[rkey].is_value = true;
        for (i = 1; i < (1 << (TREE_FAST_BITS - bits)); i++) {
            if (tree->nodes[rkey | (i << bits)].length)
                return false;
            tree->nodes[rkey | (i << bits)] = tree->nodes[rkey];
        }
        return true;
    }

    rkey &= (1 << TREE_FAST_BITS) - 1;
    if (tree->nodes[rkey].is_value)
        return false;
    tree->nodes[rkey].length = TREE_FAST_BITS + 1;
    if (!tree->nodes[rkey].value)
        tree->nodes[rkey].value = (1 << TREE_FAST_BITS) + tree->next_node++ * 2;
    i = tree->nodes[rkey].value;
    bits -= TREE_FAST_BITS;

    while (bits > 1) {
        i |= (key >> (bits - 1)) & 1;
        if (tree->nodes[i].is_value)
            return false;
        if (!tree->nodes[i].value) {
            if (tree->next_node == MAX_TREE_NODES)
                return false;
            tree->nodes[i].value = (1 << TREE_FAST_BITS) + tree->next_node++ * 2;
        }
        i = tree->nodes[i].value;
        bits--;
    }
    i |= key & 1;
    if (tree->nodes[i].value || tree->nodes[i].is_value)
        return false;
    tree->nodes[i].value = value;
    tree->nodes[i].is_value = true;

    return true;
}