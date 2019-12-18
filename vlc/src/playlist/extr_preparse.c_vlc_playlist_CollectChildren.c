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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  media_vector_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_3__ {int i_children; int /*<<< orphan*/ * p_item; struct TYPE_3__** pp_children; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_playlist_CollectChildren(vlc_playlist_t *playlist,
                             media_vector_t *dest,
                             input_item_node_t *node)
{
    vlc_playlist_AssertLocked(playlist);
    for (int i = 0; i < node->i_children; ++i)
    {
        input_item_node_t *child = node->pp_children[i];
        input_item_t *media = child->p_item;
        vlc_vector_push(dest, media);
        vlc_playlist_CollectChildren(playlist, dest, child);
    }
}