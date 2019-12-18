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
typedef  int /*<<< orphan*/  intf_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PlaylistDoVoid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_Prev ; 

__attribute__((used)) static void PlaylistPrev(intf_thread_t *intf)
{
    PlaylistDoVoid(intf, vlc_playlist_Prev);
}