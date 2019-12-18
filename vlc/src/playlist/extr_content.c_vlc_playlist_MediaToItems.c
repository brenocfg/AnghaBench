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
struct TYPE_4__ {int /*<<< orphan*/  idgen; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 
 int /*<<< orphan*/ * vlc_playlist_item_New (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_item_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vlc_playlist_MediaToItems(vlc_playlist_t *playlist, input_item_t *const media[],
                          size_t count, vlc_playlist_item_t *items[])
{
    vlc_playlist_AssertLocked(playlist);
    size_t i;
    for (i = 0; i < count; ++i)
    {
        uint64_t id = playlist->idgen++;
        items[i] = vlc_playlist_item_New(media[i], id);
        if (unlikely(!items[i]))
            break;
    }
    if (i < count)
    {
        /* allocation failure, release partial items */
        while (i)
            vlc_playlist_item_Release(items[--i]);
        return VLC_ENOMEM;
    }
    return VLC_SUCCESS;
}