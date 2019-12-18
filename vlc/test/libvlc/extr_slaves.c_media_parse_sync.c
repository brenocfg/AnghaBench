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
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  finished_event ; 
 int /*<<< orphan*/  libvlc_MediaParsedChanged ; 
 int /*<<< orphan*/  libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_event_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_parse_local ; 
 int libvlc_media_parse_with_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
media_parse_sync(libvlc_media_t *p_m)
{
    vlc_sem_t sem;
    vlc_sem_init(&sem, 0);

    libvlc_event_manager_t *p_em = libvlc_media_event_manager(p_m);
    libvlc_event_attach(p_em, libvlc_MediaParsedChanged, finished_event, &sem);

    int i_ret = libvlc_media_parse_with_options(p_m, libvlc_media_parse_local, -1);
    assert(i_ret == 0);

    vlc_sem_wait (&sem);

    libvlc_event_detach(p_em, libvlc_MediaParsedChanged, finished_event, &sem);

    vlc_sem_destroy (&sem);
}