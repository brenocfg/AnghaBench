#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_IndexOf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
vlc_playlist_FindRealIndex(vlc_playlist_t *playlist, vlc_playlist_item_t *item,
                           ssize_t index_hint)
{
    if (index_hint != -1 && (size_t) index_hint < vlc_playlist_Count(playlist))
    {
        if (item == vlc_playlist_Get(playlist, index_hint))
            /* we are lucky */
            return index_hint;
    }

    /* we are unlucky, we need to find the item */
    return vlc_playlist_IndexOf(playlist, item);
}