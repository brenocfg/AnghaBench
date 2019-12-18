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
typedef  int /*<<< orphan*/  libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaPlayerEndReached ; 
 int /*<<< orphan*/  libvlc_event_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_player_reached_end ; 
 int /*<<< orphan*/  mplayer_em (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
install_media_player_observer(libvlc_media_list_player_t * p_mlp)
{
    libvlc_event_attach(mplayer_em(p_mlp), libvlc_MediaPlayerEndReached, media_player_reached_end, p_mlp);
}