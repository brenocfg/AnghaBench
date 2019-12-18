#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* nodes; } ;
typedef  TYPE_1__ opj_tgt_tree_t ;
struct TYPE_5__ {scalar_t__ low; scalar_t__ value; int known; struct TYPE_5__* parent; } ;
typedef  TYPE_2__ opj_tgt_node_t ;
typedef  int /*<<< orphan*/  opj_bio_t ;
typedef  size_t OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_bio_write (int /*<<< orphan*/ *,int,int) ; 

void opj_tgt_encode(opj_bio_t *bio, opj_tgt_tree_t *tree, OPJ_UINT32 leafno,
                    OPJ_INT32 threshold)
{
    opj_tgt_node_t *stk[31];
    opj_tgt_node_t **stkptr;
    opj_tgt_node_t *node;
    OPJ_INT32 low;

    stkptr = stk;
    node = &tree->nodes[leafno];
    while (node->parent) {
        *stkptr++ = node;
        node = node->parent;
    }

    low = 0;
    for (;;) {
        if (low > node->low) {
            node->low = low;
        } else {
            low = node->low;
        }

        while (low < threshold) {
            if (low >= node->value) {
                if (!node->known) {
                    opj_bio_write(bio, 1, 1);
                    node->known = 1;
                }
                break;
            }
            opj_bio_write(bio, 0, 1);
            ++low;
        }

        node->low = low;
        if (stkptr == stk) {
            break;
        }
        node = *--stkptr;
    }
}