#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_children; int /*<<< orphan*/ * pp_children; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlc_media_tree_ClearChildren(input_item_node_t *root)
{
    for (int i = 0; i < root->i_children; ++i)
        input_item_node_Delete(root->pp_children[i]);

    free(root->pp_children);
    root->pp_children = NULL;
    root->i_children = 0;
}