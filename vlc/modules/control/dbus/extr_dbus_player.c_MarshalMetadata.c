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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/ * playlist; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_ARRAY ; 
 int GetInputMeta (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
MarshalMetadata( intf_thread_t *p_intf, DBusMessageIter *container )
{
    int result = VLC_SUCCESS;
    vlc_playlist_t *playlist = p_intf->p_sys->playlist;
    vlc_playlist_Lock(playlist);
    ssize_t id = vlc_playlist_GetCurrentIndex(playlist);
    if(id != -1)
    {
        vlc_playlist_item_t *plitem = vlc_playlist_Get(playlist, id);
        result = GetInputMeta(playlist, plitem, container);
    }
    else
    {   // avoid breaking the type marshalling
        DBusMessageIter a;
        if( !dbus_message_iter_open_container( container, DBUS_TYPE_ARRAY,
                                               "{sv}", &a ) ||
            !dbus_message_iter_close_container( container, &a ) )
            result = VLC_ENOMEM;
    }
    vlc_playlist_Unlock(playlist);
    return result;
}