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
struct TYPE_5__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ vlc_media_tree_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_node_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_RemoveNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_children_removed ; 
 int /*<<< orphan*/  vlc_media_tree_AssertLocked (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_media_tree_FindNodeByMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vlc_media_tree_Notify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 

bool
vlc_media_tree_Remove(vlc_media_tree_t *tree, input_item_t *media)
{
    vlc_media_tree_AssertLocked(tree);

    input_item_node_t *node;
    input_item_node_t *parent;
    if (!vlc_media_tree_FindNodeByMedia(&tree->root, media, &node, &parent))
        return false;

    input_item_node_RemoveNode(parent, node);
    vlc_media_tree_Notify(tree, on_children_removed, parent, &node, 1);
    input_item_node_Delete(node);
    return true;
}