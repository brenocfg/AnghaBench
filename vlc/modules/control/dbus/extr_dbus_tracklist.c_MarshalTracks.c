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
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/ * playlist; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  MPRIS_TRACKID_FORMAT ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int asprintf (char**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dbus_message_iter_abandon_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
MarshalTracks( intf_thread_t *p_intf, DBusMessageIter *container )
{
    DBusMessageIter tracks;
    char *psz_track_id = NULL;
    vlc_playlist_t *playlist = p_intf->p_sys->playlist;

    dbus_message_iter_open_container( container, DBUS_TYPE_ARRAY, "o",
                                      &tracks );

    vlc_playlist_Lock(playlist);
    size_t pl_size = vlc_playlist_Count(playlist);
    vlc_playlist_Unlock(playlist);
    for (size_t i = 0; i < pl_size; i++)
    {
        if (asprintf(&psz_track_id, MPRIS_TRACKID_FORMAT, i) == -1 ||
            !dbus_message_iter_append_basic( &tracks,
                                             DBUS_TYPE_OBJECT_PATH,
                                             &psz_track_id ) )
        {
            dbus_message_iter_abandon_container( container, &tracks );
            return VLC_ENOMEM;
        }

        free( psz_track_id );
    }

    if( !dbus_message_iter_close_container( container, &tracks ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}