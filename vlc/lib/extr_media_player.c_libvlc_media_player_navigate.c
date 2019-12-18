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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  map ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
typedef  enum vlc_player_nav { ____Placeholder_vlc_player_nav } vlc_player_nav ;

/* Variables and functions */
#define  VLC_PLAYER_NAV_ACTIVATE 133 
#define  VLC_PLAYER_NAV_DOWN 132 
#define  VLC_PLAYER_NAV_LEFT 131 
#define  VLC_PLAYER_NAV_POPUP 130 
#define  VLC_PLAYER_NAV_RIGHT 129 
#define  VLC_PLAYER_NAV_UP 128 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Navigate (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

void libvlc_media_player_navigate( libvlc_media_player_t* p_mi,
                                   unsigned navigate )
{
    static const enum vlc_player_nav map[] =
    {
        VLC_PLAYER_NAV_ACTIVATE, VLC_PLAYER_NAV_UP, VLC_PLAYER_NAV_DOWN,
        VLC_PLAYER_NAV_LEFT, VLC_PLAYER_NAV_RIGHT, VLC_PLAYER_NAV_POPUP,
    };

    if( navigate >= sizeof(map) / sizeof(map[0]) )
      return;

    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    vlc_player_Navigate(player, map[navigate]);

    vlc_player_Unlock(player);
}