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
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_add_media (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_player_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_play_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_set_media_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_and_wait (int /*<<< orphan*/ *) ; 
 char* test_default_sample ; 
 int /*<<< orphan*/  test_log (char*,char const*) ; 
 int /*<<< orphan*/  wait_playing (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_media_list_player_pause_stop(const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_list_t *ml;
    libvlc_media_list_player_t *mlp;

    const char * file = test_default_sample;

    test_log ("Testing play and pause of %s using the media list.\n", file);

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    md = libvlc_media_new_path (vlc, file);
    assert(md);

    ml = libvlc_media_list_new (vlc);
    assert (ml != NULL);

    mlp = libvlc_media_list_player_new (vlc);
    assert(mlp);

    libvlc_media_list_add_media( ml, md);

    libvlc_media_list_player_set_media_list( mlp, ml );

    libvlc_media_list_player_play_item( mlp, md );

    wait_playing (mlp);

    libvlc_media_list_player_pause (mlp);

    stop_and_wait (mlp);

    libvlc_media_release (md);
    libvlc_media_list_player_release (mlp);
    libvlc_release (vlc);
}