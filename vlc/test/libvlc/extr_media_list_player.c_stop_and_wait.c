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
typedef  int /*<<< orphan*/  libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_list_player_stop_async (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_stopped (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void stop_and_wait(libvlc_media_list_player_t *mlp)
{
    libvlc_media_list_player_stop_async (mlp);
    wait_stopped (mlp);
}