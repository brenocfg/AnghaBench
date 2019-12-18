#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ users; int /*<<< orphan*/  lock_manage; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_manage; int /*<<< orphan*/  thread; struct TYPE_8__* p_vod; int /*<<< orphan*/  p_module; int /*<<< orphan*/  schedule; int /*<<< orphan*/  i_schedule; int /*<<< orphan*/  media; int /*<<< orphan*/  i_media; } ;
typedef  TYPE_1__ vlm_t ;
struct TYPE_9__ {TYPE_1__* p_vlm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLM_CLEAR_MEDIAS ; 
 int /*<<< orphan*/  VLM_CLEAR_SCHEDULES ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* libvlc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 
 int /*<<< orphan*/  vlm_ControlInternal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlm_mutex ; 

void vlm_Delete( vlm_t *p_vlm )
{
    /* vlm_Delete() is serialized against itself, and against vlm_New().
     * This mutex protects libvlc_priv->p_vlm and p_vlm->users. */
    vlc_mutex_lock( &vlm_mutex );
    assert( p_vlm->users > 0 );
    if( --p_vlm->users == 0 )
        assert( libvlc_priv(vlc_object_instance(p_vlm))->p_vlm == p_vlm );
    else
        p_vlm = NULL;

    if( p_vlm == NULL )
    {
        vlc_mutex_unlock( &vlm_mutex );
        return;
    }

    /* Destroy and release VLM */
    vlc_mutex_lock( &p_vlm->lock );
    vlm_ControlInternal( p_vlm, VLM_CLEAR_MEDIAS );
    TAB_CLEAN( p_vlm->i_media, p_vlm->media );

    vlm_ControlInternal( p_vlm, VLM_CLEAR_SCHEDULES );
    TAB_CLEAN( p_vlm->i_schedule, p_vlm->schedule );
    vlc_mutex_unlock( &p_vlm->lock );

    vlc_cancel( p_vlm->thread );

    if( p_vlm->p_vod )
    {
        module_unneed( p_vlm->p_vod, p_vlm->p_vod->p_module );
        vlc_object_delete(p_vlm->p_vod);
    }

    libvlc_priv(vlc_object_instance(p_vlm))->p_vlm = NULL;
    vlc_mutex_unlock( &vlm_mutex );

    vlc_join( p_vlm->thread, NULL );

    vlc_cond_destroy( &p_vlm->wait_manage );
    vlc_mutex_destroy( &p_vlm->lock );
    vlc_mutex_destroy( &p_vlm->lock_manage );
    vlc_object_delete(p_vlm);
}