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
struct TYPE_4__ {scalar_t__ numnodes; TYPE_2__* nodes; } ;
typedef  TYPE_1__ opj_tgt_tree_t ;
struct TYPE_5__ {int value; scalar_t__ known; scalar_t__ low; } ;
typedef  TYPE_2__ opj_tgt_node_t ;
typedef  scalar_t__ OPJ_UINT32 ;

/* Variables and functions */

void opj_tgt_reset(opj_tgt_tree_t *p_tree)
{
    OPJ_UINT32 i;
    opj_tgt_node_t * l_current_node = 00;;

    if (! p_tree) {
        return;
    }

    l_current_node = p_tree->nodes;
    for (i = 0; i < p_tree->numnodes; ++i) {
        l_current_node->value = 999;
        l_current_node->low = 0;
        l_current_node->known = 0;
        ++l_current_node;
    }
}