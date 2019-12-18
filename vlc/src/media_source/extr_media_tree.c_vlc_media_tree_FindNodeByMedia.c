#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_5__ {int i_children; int /*<<< orphan*/  const* p_item; struct TYPE_5__** pp_children; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */

__attribute__((used)) static bool
vlc_media_tree_FindNodeByMedia(input_item_node_t *parent,
                               const input_item_t *media,
                               input_item_node_t **result,
                               input_item_node_t **result_parent)
{
    for (int i = 0; i < parent->i_children; ++i)
    {
        input_item_node_t *child = parent->pp_children[i];
        if (child->p_item == media)
        {
            *result = child;
            if (result_parent)
                *result_parent = parent;
            return true;
        }

        if (vlc_media_tree_FindNodeByMedia(child, media, result, result_parent))
            return true;
    }

    return false;
}