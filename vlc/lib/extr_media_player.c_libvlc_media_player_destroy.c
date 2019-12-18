#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_http_cookie_jar_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p_libvlc_instance; scalar_t__ p_md; int /*<<< orphan*/  event_manager; int /*<<< orphan*/  player; int /*<<< orphan*/  listener; int /*<<< orphan*/  aout_listener; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_event_manager_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (scalar_t__) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_detach_preparsed_event (scalar_t__) ; 
 int /*<<< orphan*/  snapshot_was_taken ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  var_Destroy (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * var_GetAddress (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_http_cookies_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_RemoveListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_aout_RemoveListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void libvlc_media_player_destroy( libvlc_media_player_t *p_mi )
{
    assert( p_mi );

    /* Detach Callback from the main libvlc object */
    var_DelCallback( vlc_object_instance(p_mi),
                     "snapshot-file", snapshot_was_taken, p_mi );

    vlc_player_Lock(p_mi->player);
    vlc_player_aout_RemoveListener(p_mi->player, p_mi->aout_listener);
    vlc_player_RemoveListener(p_mi->player, p_mi->listener);
    vlc_player_Unlock(p_mi->player);

    vlc_player_Delete(p_mi->player);

    if (p_mi->p_md)
        media_detach_preparsed_event(p_mi->p_md);
    libvlc_event_manager_destroy(&p_mi->event_manager);
    libvlc_media_release( p_mi->p_md );

    vlc_http_cookie_jar_t *cookies = var_GetAddress( p_mi, "http-cookies" );
    if ( cookies )
    {
        var_Destroy( p_mi, "http-cookies" );
        vlc_http_cookies_destroy( cookies );
    }

    libvlc_instance_t *instance = p_mi->p_libvlc_instance;
    vlc_object_delete(p_mi);
    libvlc_release(instance);
}