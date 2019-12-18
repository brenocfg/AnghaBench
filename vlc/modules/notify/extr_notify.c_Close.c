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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; scalar_t__ notification; int /*<<< orphan*/  player_listener; int /*<<< orphan*/  playlist; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_object_unref (scalar_t__) ; 
 int /*<<< orphan*/  notify_notification_close (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  notify_uninit () ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    intf_thread_t   *p_intf = ( intf_thread_t* ) p_this;
    intf_sys_t      *p_sys  = p_intf->p_sys;

    vlc_player_t *player = vlc_playlist_GetPlayer(p_sys->playlist);
    vlc_player_Lock(player);
    vlc_player_RemoveListener(player, p_sys->player_listener);
    vlc_player_Unlock(player);

    if( p_sys->notification )
    {
        GError *p_error = NULL;
        notify_notification_close( p_sys->notification, &p_error );
        g_object_unref( p_sys->notification );
    }

    vlc_mutex_destroy( &p_sys->lock );
    free( p_sys );
    notify_uninit();
}