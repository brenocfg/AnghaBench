#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_renderer_item_t ;
struct TYPE_4__ {int /*<<< orphan*/ * renderer; } ;
typedef  TYPE_1__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_player_assert_locked (TYPE_1__*) ; 

vlc_renderer_item_t *
vlc_player_GetRenderer(vlc_player_t *player)
{
    vlc_player_assert_locked(player);
    return player->renderer;
}