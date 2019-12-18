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
typedef  int /*<<< orphan*/  vlc_media_tree_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  on_children_added ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * vlc_media_tree_AddChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_AssertLocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 

input_item_node_t *
vlc_media_tree_Add(vlc_media_tree_t *tree, input_item_node_t *parent,
                   input_item_t *media)
{
    vlc_media_tree_AssertLocked(tree);

    input_item_node_t *node = vlc_media_tree_AddChild(parent, media);
    if (unlikely(!node))
        return NULL;

    vlc_media_tree_Notify(tree, on_children_added, parent, &node, 1);

    return node;
}