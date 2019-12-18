#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_children; int /*<<< orphan*/  p_item; struct TYPE_6__** pp_children; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 
 TYPE_1__* vlc_media_tree_AddChild (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlc_media_tree_AddSubtree(input_item_node_t *to, input_item_node_t *from)
{
    for (int i = 0; i < from->i_children; ++i)
    {
        input_item_node_t *child = from->pp_children[i];
        input_item_node_t *node = vlc_media_tree_AddChild(to, child->p_item);
        if (unlikely(!node))
            break; /* what could we do? */

        vlc_media_tree_AddSubtree(node, child);
    }
}