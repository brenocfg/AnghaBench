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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ media_vector_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 TYPE_1__ VLC_VECTOR_INITIALIZER ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_CollectChildren (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int vlc_playlist_Expand (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vector_destroy (TYPE_1__*) ; 

int
vlc_playlist_ExpandItem(vlc_playlist_t *playlist, size_t index,
                        input_item_node_t *node)
{
    vlc_playlist_AssertLocked(playlist);

    media_vector_t flatten = VLC_VECTOR_INITIALIZER;
    vlc_playlist_CollectChildren(playlist, &flatten, node);

    int ret = vlc_playlist_Expand(playlist, index, flatten.data, flatten.size);
    vlc_vector_destroy(&flatten);

    return ret;
}