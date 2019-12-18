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
 int /*<<< orphan*/ * libvlc_media_player_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_set_media (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_stop_async (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  play_and_wait (int /*<<< orphan*/ *) ; 
 char* test_default_sample ; 
 int /*<<< orphan*/  test_log (char*) ; 

__attribute__((used)) static void test_media_player_set_media(const char** argv, int argc)
{
    const char * file = test_default_sample;

    test_log ("Testing set_media\n");

    libvlc_instance_t *vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    libvlc_media_t *md = libvlc_media_new_path (vlc, file);
    assert (md != NULL);

    libvlc_media_player_t *mp = libvlc_media_player_new (vlc);
    assert (mp != NULL);

    libvlc_media_player_set_media (mp, md);

    libvlc_media_release (md);

    play_and_wait(mp);

    libvlc_media_player_stop_async (mp);
    libvlc_media_player_release (mp);
    libvlc_release (vlc);
}