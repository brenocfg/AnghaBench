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
 int /*<<< orphan*/  test_defaults_args ; 
 int /*<<< orphan*/  test_defaults_nargs ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_media_player_pause_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_player_play_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_media_player_set_media (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main (void)
{
    test_init();

    test_media_player_set_media (test_defaults_args, test_defaults_nargs);
    test_media_player_play_stop (test_defaults_args, test_defaults_nargs);
    test_media_player_pause_stop (test_defaults_args, test_defaults_nargs);

    return 0;
}