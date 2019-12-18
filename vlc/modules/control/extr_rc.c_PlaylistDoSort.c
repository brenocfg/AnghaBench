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
struct vlc_playlist_sort_criterion {int /*<<< orphan*/  order; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_KEY_ARTIST ; 
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_ORDER_ASCENDING ; 
 int vlc_playlist_Sort (int /*<<< orphan*/ *,struct vlc_playlist_sort_criterion*,int) ; 

__attribute__((used)) static int PlaylistDoSort(vlc_playlist_t *playlist)
{
    struct vlc_playlist_sort_criterion criteria =
    {
        .key = VLC_PLAYLIST_SORT_KEY_ARTIST,
        .order = VLC_PLAYLIST_SORT_ORDER_ASCENDING
    };

    return vlc_playlist_Sort(playlist, &criteria, 1);
}