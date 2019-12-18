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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_6__ {int i_socket; int /*<<< orphan*/  status_lock; struct TYPE_6__* psz_unix_path; int /*<<< orphan*/  pi_socket_listen; int /*<<< orphan*/  thread; int /*<<< orphan*/  player_listener; int /*<<< orphan*/  player_aout_listener; int /*<<< orphan*/  playlist; } ;
typedef  TYPE_2__ intf_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int /*<<< orphan*/  net_ListenClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_aout_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Deactivate( vlc_object_t *p_this )
{
    intf_thread_t *p_intf = (intf_thread_t*)p_this;
    intf_sys_t *p_sys = p_intf->p_sys;

    vlc_player_t *player = vlc_playlist_GetPlayer(p_sys->playlist);
    vlc_player_Lock(player);
    vlc_player_aout_RemoveListener(player, p_sys->player_aout_listener);
    vlc_player_RemoveListener(player, p_sys->player_listener);
    vlc_player_Unlock(player);

    vlc_cancel( p_sys->thread );
    vlc_join( p_sys->thread, NULL );

    net_ListenClose( p_sys->pi_socket_listen );
    if( p_sys->i_socket != -1 )
        net_Close( p_sys->i_socket );
#if defined(AF_LOCAL) && !defined(_WIN32)
    if( p_sys->psz_unix_path != NULL )
    {
        unlink( p_sys->psz_unix_path );
        free( p_sys->psz_unix_path );
    }
#endif
    vlc_mutex_destroy( &p_sys->status_lock );
    free( p_sys );
}