#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {scalar_t__ order; TYPE_1__ items; int /*<<< orphan*/  randomizer; int /*<<< orphan*/  idgen; } ;
typedef  TYPE_2__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  randomizer_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  randomizer_Remove (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ItemReplaced (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/ * vlc_playlist_item_New (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_item_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vlc_playlist_Replace(vlc_playlist_t *playlist, size_t index,
                     input_item_t *media)
{
    vlc_playlist_AssertLocked(playlist);
    assert(index < playlist->items.size);

    uint64_t id = playlist->idgen++;
    vlc_playlist_item_t *item = vlc_playlist_item_New(media, id);
    if (!item)
        return VLC_ENOMEM;

    if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
    {
        randomizer_Remove(&playlist->randomizer,
                          &playlist->items.data[index], 1);
        randomizer_Add(&playlist->randomizer, &item, 1);
    }

    vlc_playlist_item_Release(playlist->items.data[index]);
    playlist->items.data[index] = item;

    vlc_playlist_ItemReplaced(playlist, index);
    return VLC_SUCCESS;
}