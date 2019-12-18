#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int users; int input_state_changed; int i_id; int /*<<< orphan*/  lock_manage; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_manage; int /*<<< orphan*/  thread; int /*<<< orphan*/ * p_vod; int /*<<< orphan*/  schedule; int /*<<< orphan*/  i_schedule; int /*<<< orphan*/  media; int /*<<< orphan*/  i_media; } ;
typedef  TYPE_1__ vlm_t ;
typedef  int /*<<< orphan*/  vlm_message_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_10__ {TYPE_1__* p_vlm; } ;

/* Variables and functions */
 int /*<<< orphan*/  Manage ; 
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UINT_MAX ; 
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  VLC_VAR_ADDRESS ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_8__* libvlc_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_Create (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init_daytime (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 scalar_t__ vlm_ExecuteCommand (TYPE_1__*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vlm_MessageDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlm_mutex ; 

vlm_t *vlm_New( libvlc_int_t *libvlc, const char *psz_vlmconf )
{
    vlm_t *p_vlm = NULL, **pp_vlm = &(libvlc_priv(libvlc)->p_vlm);
    vlc_object_t *p_this = VLC_OBJECT(libvlc);

    /* Avoid multiple creation */
    vlc_mutex_lock( &vlm_mutex );

    p_vlm = *pp_vlm;
    if( p_vlm )
    {   /* VLM already exists */
        if( likely( p_vlm->users < UINT_MAX ) )
            p_vlm->users++;
        else
            p_vlm = NULL;
        vlc_mutex_unlock( &vlm_mutex );
        return p_vlm;
    }

    msg_Dbg( p_this, "creating VLM" );

    p_vlm = vlc_custom_create( p_this, sizeof( *p_vlm ), "vlm daemon" );
    if( !p_vlm )
    {
        vlc_mutex_unlock( &vlm_mutex );
        return NULL;
    }

    vlc_mutex_init( &p_vlm->lock );
    vlc_mutex_init( &p_vlm->lock_manage );
    vlc_cond_init_daytime( &p_vlm->wait_manage );
    p_vlm->users = 1;
    p_vlm->input_state_changed = false;
    p_vlm->i_id = 1;
    TAB_INIT( p_vlm->i_media, p_vlm->media );
    TAB_INIT( p_vlm->i_schedule, p_vlm->schedule );
    p_vlm->p_vod = NULL;
    var_Create( p_vlm, "intf-event", VLC_VAR_ADDRESS );

    if( vlc_clone( &p_vlm->thread, Manage, p_vlm, VLC_THREAD_PRIORITY_LOW ) )
    {
        vlc_cond_destroy( &p_vlm->wait_manage );
        vlc_mutex_destroy( &p_vlm->lock );
        vlc_mutex_destroy( &p_vlm->lock_manage );
        vlc_object_delete(p_vlm);
        vlc_mutex_unlock( &vlm_mutex );
        return NULL;
    }

    *pp_vlm = p_vlm; /* for future reference */

    vlc_mutex_unlock( &vlm_mutex );

    /* Load our configuration file */
    if( psz_vlmconf != NULL )
    {
        vlm_message_t *p_message = NULL;
        char *psz_buffer = NULL;

        msg_Dbg( p_this, "loading VLM configuration" );
        if( asprintf(&psz_buffer, "load %s", psz_vlmconf ) != -1 )
        {
            msg_Dbg( p_this, "%s", psz_buffer );
            if( vlm_ExecuteCommand( p_vlm, psz_buffer, &p_message ) )
                msg_Warn( p_this, "error while loading the configuration file" );

            vlm_MessageDelete( p_message );
            free( psz_buffer );
        }
    }

    return p_vlm;
}