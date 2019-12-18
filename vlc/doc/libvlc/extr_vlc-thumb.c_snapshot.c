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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callback ; 
 int done ; 
 int /*<<< orphan*/  event_wait (char*) ; 
 int /*<<< orphan*/  libvlc_MediaPlayerSnapshotTaken ; 
 int /*<<< orphan*/  libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_player_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_video_take_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snapshot(libvlc_media_player_t *mp, int width, char *out_with_ext)
{
    libvlc_event_manager_t *em = libvlc_media_player_event_manager(mp);
    assert(em);

    libvlc_event_attach(em, libvlc_MediaPlayerSnapshotTaken, callback, NULL);
    done = false;
    libvlc_video_take_snapshot(mp, 0, out_with_ext, width, 0);
    event_wait("Snapshot has not been written");
    libvlc_event_detach(em, libvlc_MediaPlayerSnapshotTaken, callback, NULL);
}