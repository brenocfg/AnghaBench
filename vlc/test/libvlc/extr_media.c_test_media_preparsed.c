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
typedef  scalar_t__ libvlc_media_parsed_status_t ;
typedef  int /*<<< orphan*/  libvlc_media_parse_flag_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  libvlc_MediaParsedChanged ; 
 int /*<<< orphan*/  libvlc_event_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_event_manager (int /*<<< orphan*/ *) ; 
 scalar_t__ libvlc_media_get_parsed_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_new_location (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int libvlc_media_parse_with_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ libvlc_media_parsed_status_done ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_parse_ended ; 
 int /*<<< orphan*/  print_media (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_log (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_media_preparsed(libvlc_instance_t *vlc, const char *path,
                                 const char *location,
                                 libvlc_media_parse_flag_t parse_flags,
                                 libvlc_media_parsed_status_t i_expected_status)
{
    test_log ("test_media_preparsed: %s, expected: %d\n", path ? path : location,
              i_expected_status);

    libvlc_media_t *media;
    if (path != NULL)
        media = libvlc_media_new_path (vlc, path);
    else
        media = libvlc_media_new_location (vlc, location);
    assert (media != NULL);

    vlc_sem_t sem;
    vlc_sem_init (&sem, 0);

    // Check to see if we are properly receiving the event.
    libvlc_event_manager_t *em = libvlc_media_event_manager (media);
    libvlc_event_attach (em, libvlc_MediaParsedChanged, media_parse_ended, &sem);

    // Parse the media. This is synchronous.
    int i_ret = libvlc_media_parse_with_options(media, parse_flags, -1);
    assert(i_ret == 0);

    // Wait for preparsed event
    vlc_sem_wait (&sem);
    vlc_sem_destroy (&sem);

    // We are good, now check Elementary Stream info.
    assert (libvlc_media_get_parsed_status(media) == i_expected_status);
    if (i_expected_status == libvlc_media_parsed_status_done)
        print_media(media);

    libvlc_media_release (media);
}