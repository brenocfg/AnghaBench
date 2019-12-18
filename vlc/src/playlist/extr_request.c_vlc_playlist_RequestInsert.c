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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int vlc_playlist_Insert (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ * const*,size_t) ; 

int
vlc_playlist_RequestInsert(vlc_playlist_t *playlist, size_t index,
                           input_item_t *const media[], size_t count)
{
    vlc_playlist_AssertLocked(playlist);

    size_t size = vlc_playlist_Count(playlist);
    if (index > size)
        index = size;

    return vlc_playlist_Insert(playlist, index, media, count);
}