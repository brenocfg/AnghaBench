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
 int /*<<< orphan*/  on_children_reset ; 
 int /*<<< orphan*/  vlc_media_tree_AddSubtree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_ClearChildren (int /*<<< orphan*/ *) ; 
 int vlc_media_tree_FindNodeByMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Notify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Unlock (TYPE_1__*) ; 

__attribute__((used)) static void
media_subtree_changed(input_item_t *media, input_item_node_t *node,
                      void *userdata)
{
    vlc_media_tree_t *tree = userdata;

    vlc_media_tree_Lock(tree);
    input_item_node_t *subtree_root;
    /* TODO retrieve the node without traversing the tree */
    bool found = vlc_media_tree_FindNodeByMedia(&tree->root, media,
                                                &subtree_root, NULL);
    if (!found) {
        /* the node probably failed to be allocated */
        vlc_media_tree_Unlock(tree);
        return;
    }

    vlc_media_tree_ClearChildren(subtree_root);
    vlc_media_tree_AddSubtree(subtree_root, node);
    vlc_media_tree_Notify(tree, on_children_reset, subtree_root);
    vlc_media_tree_Unlock(tree);
}