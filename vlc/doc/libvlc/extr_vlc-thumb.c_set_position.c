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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THUMBNAIL_POSITION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callback ; 
 int done ; 
 int /*<<< orphan*/  event_wait (char*) ; 
 int /*<<< orphan*/  libvlc_MediaPlayerPositionChanged ; 
 int /*<<< orphan*/  libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_player_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_set_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_position(libvlc_media_player_t *mp)
{
    libvlc_event_manager_t *em = libvlc_media_player_event_manager(mp);
    assert(em);

    libvlc_event_attach(em, libvlc_MediaPlayerPositionChanged, callback, NULL);
    done = false;
    libvlc_media_player_set_position(mp, VLC_THUMBNAIL_POSITION);
    event_wait("Couldn't set position");
    libvlc_event_detach(em, libvlc_MediaPlayerPositionChanged, callback, NULL);
}