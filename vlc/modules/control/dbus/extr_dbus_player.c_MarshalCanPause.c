#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_4__ {int /*<<< orphan*/  playlist; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_CanPause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
MarshalCanPause( intf_thread_t *p_intf, DBusMessageIter *container )
{
    vlc_player_t *player = vlc_playlist_GetPlayer(p_intf->p_sys->playlist);
    vlc_player_Lock(player);
    dbus_bool_t b_can_pause = vlc_player_CanPause(player);
    vlc_player_Unlock(player);

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_pause ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}