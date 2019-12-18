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
struct vlc_playlist_view {int /*<<< orphan*/  playlist; } ;

/* Variables and functions */
 size_t vlc_playlist_Count (int /*<<< orphan*/ ) ; 

size_t
vlc_playlist_view_Count(struct vlc_playlist_view *view)
{
    return vlc_playlist_Count(view->playlist);
}