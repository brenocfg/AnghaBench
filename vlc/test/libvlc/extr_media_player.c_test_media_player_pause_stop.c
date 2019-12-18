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
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * libvlc_media_player_new_from_media (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_stop_async (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause_and_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  play_and_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_audio_video (int /*<<< orphan*/ *) ; 
 char* test_default_sample ; 
 int /*<<< orphan*/  test_log (char*,char const*) ; 
 int /*<<< orphan*/  test_role (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_media_player_pause_stop(const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_player_t *mi;
    const char * file = test_default_sample;

    test_log ("Testing pause and stop of %s\n", file);

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    md = libvlc_media_new_path (vlc, file);
    assert (md != NULL);

    mi = libvlc_media_player_new_from_media (md);
    assert (mi != NULL);

    libvlc_media_release (md);

    test_audio_video(mi);
    test_role(mi);

    play_and_wait(mi);
    test_audio_video(mi);

    pause_and_wait(mi);
    test_audio_video(mi);

    libvlc_media_player_stop_async (mi);
    test_audio_video(mi);

    libvlc_media_player_release (mi);
    libvlc_release (vlc);
}