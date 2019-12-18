#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** vlc_player_vout_HoldAll (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static vout_thread_t **GetVouts( libvlc_media_player_t *p_mi, size_t *n )
{
    vlc_player_t *player = p_mi->player;
    return vlc_player_vout_HoldAll(player, n);
}