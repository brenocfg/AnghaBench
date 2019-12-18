#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {TYPE_4__* b25stream; scalar_t__ p_instance; } ;
struct TYPE_12__ {int /*<<< orphan*/  attachments; int /*<<< orphan*/  pids; int /*<<< orphan*/  csa_lock; TYPE_1__ arib; int /*<<< orphan*/  programs; scalar_t__ csa; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChangeKeyCallback ; 
 int /*<<< orphan*/  FreeDictAttachment ; 
 int /*<<< orphan*/  GetPID (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDRelease (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arib_instance_destroy (scalar_t__) ; 
 int /*<<< orphan*/  csa_Delete (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  ts_pid_list_Release (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_2__*,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Delete (TYPE_4__*) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    PIDRelease( p_demux, GetPID(p_sys, 0) );

    vlc_mutex_lock( &p_sys->csa_lock );
    if( p_sys->csa )
    {
        var_DelCallback( p_demux, "ts-csa-ck", ChangeKeyCallback, (void *)1 );
        var_DelCallback( p_demux, "ts-csa2-ck", ChangeKeyCallback, NULL );
        csa_Delete( p_sys->csa );
    }
    vlc_mutex_unlock( &p_sys->csa_lock );

    ARRAY_RESET( p_sys->programs );

#ifdef HAVE_ARIBB24
    if ( p_sys->arib.p_instance )
        arib_instance_destroy( p_sys->arib.p_instance );
#endif

    if ( p_sys->arib.b25stream )
    {
        p_sys->arib.b25stream->s = NULL; /* don't chain kill demuxer's source */
        vlc_stream_Delete( p_sys->arib.b25stream );
    }

    vlc_mutex_destroy( &p_sys->csa_lock );

    /* Release all non default pids */
    ts_pid_list_Release( p_demux, &p_sys->pids );

    /* Clear up attachments */
    vlc_dictionary_clear( &p_sys->attachments, FreeDictAttachment, NULL );

    free( p_sys );
}