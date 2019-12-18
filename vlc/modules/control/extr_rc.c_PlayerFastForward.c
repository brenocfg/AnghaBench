#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_6__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/ * playlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIONID_JUMP_FORWARD_EXTRASHORT ; 
 scalar_t__ isgreater (float,float) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_2__*) ; 
 scalar_t__ vlc_player_CanChangeRate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_ChangeRate (int /*<<< orphan*/ *,float) ; 
 float vlc_player_GetRate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PlayerFastForward(intf_thread_t *intf)
{
    vlc_playlist_t *playlist = intf->p_sys->playlist;
    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);

    vlc_player_Lock(player);
    if (vlc_player_CanChangeRate(player))
    {
        float rate = vlc_player_GetRate(player);
        vlc_player_ChangeRate(player,
                              isgreater(rate, 0.f) ? rate * 2.f : -rate);
    }
    else
        var_SetInteger(vlc_object_instance(intf), "key-action",
                       ACTIONID_JUMP_FORWARD_EXTRASHORT);
    vlc_player_Unlock(player);
}