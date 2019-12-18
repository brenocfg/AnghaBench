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
typedef  int /*<<< orphan*/  vlc_media_tree_t ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ vlc_media_tree_listener_id ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Unlock (int /*<<< orphan*/ *) ; 

void
vlc_media_tree_RemoveListener(vlc_media_tree_t *tree,
                              vlc_media_tree_listener_id *listener)
{
    vlc_media_tree_Lock(tree);
    vlc_list_remove(&listener->node);
    vlc_media_tree_Unlock(tree);

    free(listener);
}