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
typedef  enum input_item_preparse_status { ____Placeholder_input_item_preparse_status } input_item_preparse_status ;

/* Variables and functions */
 int /*<<< orphan*/  on_preparse_end ; 
 int vlc_media_tree_FindNodeByMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Notify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_media_tree_Unlock (TYPE_1__*) ; 

__attribute__((used)) static void
media_subtree_preparse_ended(input_item_t *media,
                             enum input_item_preparse_status status,
                             void *user_data)
{
    vlc_media_tree_t *tree = user_data;

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
    vlc_media_tree_Notify(tree, on_preparse_end, subtree_root, status);
    vlc_media_tree_Unlock(tree);
}