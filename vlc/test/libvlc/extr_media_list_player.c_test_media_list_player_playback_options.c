#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * p_subitems; } ;
typedef  TYPE_1__ libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_list_add_media (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_media_list_new (int /*<<< orphan*/ *) ; 
 scalar_t__ libvlc_media_list_player_is_playing (TYPE_1__*) ; 
 TYPE_1__* libvlc_media_list_player_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_play_item (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_list_player_release (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_list_player_set_media_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_player_set_playback_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_player_stop_async (TYPE_1__*) ; 
 TYPE_1__* libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  libvlc_media_release (TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_playback_mode_default ; 
 int /*<<< orphan*/  libvlc_playback_mode_loop ; 
 int /*<<< orphan*/  libvlc_playback_mode_repeat ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_list_add_file_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  stop_and_wait (TYPE_1__*) ; 
 char* test_default_sample ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  wait_playing (TYPE_1__*) ; 

__attribute__((used)) static void test_media_list_player_playback_options (const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_t *md2;
    libvlc_media_t *md3;
    libvlc_media_t *md4;
    libvlc_media_t *md5;
    libvlc_media_list_t *ml;
    libvlc_media_list_t *ml2;
    libvlc_media_list_t *ml3;
    libvlc_media_list_t *ml4;
    libvlc_media_list_t *ml5;
    libvlc_media_list_t *ml6;
    libvlc_media_list_player_t *mlp;

    const char * file = test_default_sample;

    test_log ("Testing media player playback options()\n");

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    /*
     *   Create the following media tree:
     *
     *  ml1:            0 ---- 1 ---- 2
     *                 /       |       \
     *  ml2&4:      0 -- 1     |   0 -- 1 -- 2
     *                         |
     *  ml3:    0 -- 1 -- 2 -- 3 -- 4 -- 5 -- 6
     *                    |                   |
     *  ml5&6:            0                 0 -- 1
     */

    md = libvlc_media_new_path (vlc, file);
    assert(md);

    md2 = libvlc_media_new_path (vlc, file);
    assert(md2);

    md3 = libvlc_media_new_path (vlc, file);
    assert(md3);

    md4 = libvlc_media_new_path (vlc, file);
    assert(md4);

    md5 = libvlc_media_new_path (vlc, file);
    assert(md5);

    ml = libvlc_media_list_new (vlc);
    assert (ml != NULL);

    ml2 = libvlc_media_list_new (vlc);
    assert (ml2 != NULL);

    ml3 = libvlc_media_list_new (vlc);
    assert (ml3 != NULL);

    ml4 = libvlc_media_list_new (vlc);
    assert (ml4 != NULL);

    ml5 = libvlc_media_list_new (vlc);
    assert (ml5 != NULL);

    ml6 = libvlc_media_list_new (vlc);
    assert (ml6 != NULL);

    media_list_add_file_path (vlc, ml2, file);
    media_list_add_file_path (vlc, ml2, file);

    media_list_add_file_path (vlc, ml3, file);
    media_list_add_file_path (vlc, ml3, file);
    libvlc_media_list_add_media (ml3, md4);
    media_list_add_file_path (vlc, ml3, file);
    media_list_add_file_path (vlc, ml3, file);
    media_list_add_file_path (vlc, ml3, file);
    libvlc_media_list_add_media (ml3, md5);

    media_list_add_file_path (vlc, ml4, file);
    media_list_add_file_path (vlc, ml4, file);
    media_list_add_file_path (vlc, ml4, file);

    media_list_add_file_path (vlc, ml5, file);

    media_list_add_file_path (vlc, ml6, file);
    media_list_add_file_path (vlc, ml6, file);

    md->p_subitems = ml2;
    md2->p_subitems = ml3;
    md3->p_subitems = ml4;
    md4->p_subitems = ml5;
    md5->p_subitems = ml6;

    libvlc_media_list_add_media (ml, md);
    libvlc_media_list_add_media (ml, md2);
    libvlc_media_list_add_media (ml, md3);

    mlp = libvlc_media_list_player_new (vlc);
    assert(mlp);

    libvlc_media_list_player_set_media_list (mlp, ml);

    // Test default playback mode
    libvlc_media_list_player_set_playback_mode(mlp, libvlc_playback_mode_default);

    libvlc_media_list_player_play_item (mlp, md);

    wait_playing (mlp);

    libvlc_media_release (md);
    libvlc_media_release (md2);
    libvlc_media_release (md3);
    libvlc_media_release (md4);
    libvlc_media_release (md5);

    libvlc_media_list_player_stop_async (mlp);

    while (libvlc_media_list_player_is_playing (mlp))
        sched_yield();

    // Test looping playback mode
    test_log ("Testing media player playback option - Loop\n");
    libvlc_media_list_player_set_playback_mode(mlp, libvlc_playback_mode_loop);

    libvlc_media_list_player_play_item (mlp, md);

    wait_playing (mlp);

    stop_and_wait (mlp);

    // Test repeat playback mode
    test_log ("Testing media player playback option - Repeat\n");
    libvlc_media_list_player_set_playback_mode(mlp, libvlc_playback_mode_repeat);

    libvlc_media_list_player_play_item (mlp, md);

    wait_playing (mlp);

    stop_and_wait (mlp);

    libvlc_media_list_player_release (mlp);
    libvlc_release (vlc);
}