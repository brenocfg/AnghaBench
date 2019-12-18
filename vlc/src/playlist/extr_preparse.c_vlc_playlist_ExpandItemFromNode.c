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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_item; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int VLC_ENOITEM ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 
 int vlc_playlist_ExpandItem (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int vlc_playlist_IndexOfMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
vlc_playlist_ExpandItemFromNode(vlc_playlist_t *playlist,
                                input_item_node_t *subitems)
{
    vlc_playlist_AssertLocked(playlist);
    input_item_t *media = subitems->p_item;
    ssize_t index = vlc_playlist_IndexOfMedia(playlist, media);
    if (index == -1)
        return VLC_ENOITEM;

    /* replace the item by its flatten subtree */
    return vlc_playlist_ExpandItem(playlist, index, subitems);
}