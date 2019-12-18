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
typedef  scalar_t__ dbus_int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  playlist; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INT64 ; 
 scalar_t__ US_FROM_VLC_TICK (scalar_t__) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ vlc_player_GetTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
MarshalPosition( intf_thread_t *p_intf, DBusMessageIter *container )
{
    /* returns time in microseconds */
    dbus_int64_t i_pos;

    vlc_player_t *player = vlc_playlist_GetPlayer(p_intf->p_sys->playlist);
    vlc_player_Lock(player);
    i_pos = vlc_player_GetTime(player);
    vlc_player_Unlock(player);
    i_pos = i_pos == VLC_TICK_INVALID ? 0 : US_FROM_VLC_TICK(i_pos);

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_INT64, &i_pos ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}