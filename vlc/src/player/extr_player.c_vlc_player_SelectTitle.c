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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_title {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int vlc_player_GetTitleIdx (int /*<<< orphan*/ *,struct vlc_player_title const*) ; 
 int /*<<< orphan*/  vlc_player_SelectTitleIdx (int /*<<< orphan*/ *,int) ; 

void
vlc_player_SelectTitle(vlc_player_t *player,
                       const struct vlc_player_title *title)
{
    ssize_t idx = vlc_player_GetTitleIdx(player, title);
    if (idx != -1)
        vlc_player_SelectTitleIdx(player, idx);
}