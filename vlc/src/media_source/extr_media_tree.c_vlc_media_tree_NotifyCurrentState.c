#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ vlc_media_tree_t ;
typedef  int /*<<< orphan*/  vlc_media_tree_listener_id ;

/* Variables and functions */
 int /*<<< orphan*/  on_children_reset ; 
 int /*<<< orphan*/  vlc_media_tree_NotifyListener (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_media_tree_NotifyCurrentState(vlc_media_tree_t *tree,
                                  vlc_media_tree_listener_id *listener)
{
    vlc_media_tree_NotifyListener(tree, listener, on_children_reset,
                                  &tree->root);
}