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

/* Variables and functions */
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  test_defaults_args ; 
 int /*<<< orphan*/  test_defaults_nargs ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_media_list_player_items_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_list_player_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_list_player_pause_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_list_player_play_item_at_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_list_player_playback_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_list_player_previous (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (void)
{
    test_init();

    // There are 6 tests. And they take some times.
    alarm(6 * 5);

    test_media_list_player_pause_stop (test_defaults_args, test_defaults_nargs);
    test_media_list_player_play_item_at_index (test_defaults_args, test_defaults_nargs);
    test_media_list_player_previous (test_defaults_args, test_defaults_nargs);
    test_media_list_player_next (test_defaults_args, test_defaults_nargs);
    test_media_list_player_items_queue (test_defaults_args, test_defaults_nargs);
    test_media_list_player_playback_options (test_defaults_args, test_defaults_nargs);
    return 0;
}