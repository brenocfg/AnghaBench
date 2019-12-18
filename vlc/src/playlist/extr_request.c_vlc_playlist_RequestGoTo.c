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
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 
 int vlc_playlist_FindRealIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_GoTo (int /*<<< orphan*/ *,int) ; 

int
vlc_playlist_RequestGoTo(vlc_playlist_t *playlist, vlc_playlist_item_t *item,
                         ssize_t index_hint)
{
    vlc_playlist_AssertLocked(playlist);
    ssize_t real_index = item
                       ? vlc_playlist_FindRealIndex(playlist, item, index_hint)
                       : -1;
    return vlc_playlist_GoTo(playlist, real_index);
}