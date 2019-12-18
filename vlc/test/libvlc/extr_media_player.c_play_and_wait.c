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
typedef  int /*<<< orphan*/  vlc_sem_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  libvlc_MediaPlayerPlaying ; 
 int libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_player_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_event ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void play_and_wait(libvlc_media_player_t *mp)
{
    libvlc_event_manager_t *em = libvlc_media_player_event_manager(mp);

    vlc_sem_t sem;
    vlc_sem_init(&sem, 0);

    int res;
    res = libvlc_event_attach(em, libvlc_MediaPlayerPlaying, on_event, &sem);
    assert(!res);

    libvlc_media_player_play(mp);

    test_log("Waiting for playing\n");
    vlc_sem_wait(&sem);

    libvlc_event_detach(em, libvlc_MediaPlayerPlaying, on_event, &sem);

    vlc_sem_destroy(&sem);
}