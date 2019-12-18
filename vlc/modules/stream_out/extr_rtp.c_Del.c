#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ sout_stream_t ;
struct TYPE_18__ {int /*<<< orphan*/ * psz_sdp_file; scalar_t__ b_export_sap; int /*<<< orphan*/  rtsp; int /*<<< orphan*/  psz_vod_session; int /*<<< orphan*/ * p_vod_media; int /*<<< orphan*/  lock_es; int /*<<< orphan*/  es; int /*<<< orphan*/  i_es; } ;
typedef  TYPE_5__ sout_stream_sys_t ;
struct TYPE_15__ {int /*<<< orphan*/ * fd; int /*<<< orphan*/  thread; } ;
struct TYPE_14__ {TYPE_6__* fmtp; } ;
struct TYPE_19__ {scalar_t__ sinkc; int /*<<< orphan*/  lock_sink; int /*<<< orphan*/ * srtp; TYPE_3__* sinkv; TYPE_2__ listen; scalar_t__ rtsp_id; TYPE_1__ rtp_fmt; int /*<<< orphan*/ * p_fifo; int /*<<< orphan*/  thread; } ;
typedef  TYPE_6__ sout_stream_id_sys_t ;
struct TYPE_16__ {int /*<<< orphan*/  rtp_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FileSetup (TYPE_4__*) ; 
 int /*<<< orphan*/  RtspDelId (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SapSetup (TYPE_4__*) ; 
 int /*<<< orphan*/  TAB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_ListenClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_del_sink (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srtp_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vod_detach_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *_id )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;

    vlc_mutex_lock( &p_sys->lock_es );
    TAB_REMOVE( p_sys->i_es, p_sys->es, id );
    vlc_mutex_unlock( &p_sys->lock_es );

    if( likely(id->p_fifo != NULL) )
    {
        vlc_cancel( id->thread );
        vlc_join( id->thread, NULL );
        block_FifoRelease( id->p_fifo );
    }

    free( id->rtp_fmt.fmtp );

    if (p_sys->p_vod_media != NULL)
        vod_detach_id(p_sys->p_vod_media, p_sys->psz_vod_session, id);
    if( id->rtsp_id )
        RtspDelId( p_sys->rtsp, id->rtsp_id );
    if( id->listen.fd != NULL )
    {
        vlc_cancel( id->listen.thread );
        vlc_join( id->listen.thread, NULL );
        net_ListenClose( id->listen.fd );
    }
    /* Delete remaining sinks (incoming connections or explicit
     * outgoing dst=) */
    while( id->sinkc > 0 )
        rtp_del_sink( id, id->sinkv[0].rtp_fd );
#ifdef HAVE_SRTP
    if( id->srtp != NULL )
        srtp_destroy( id->srtp );
#endif

    vlc_mutex_destroy( &id->lock_sink );

    /* Update SDP (sap/file) */
    if( p_sys->b_export_sap ) SapSetup( p_stream );
    if( p_sys->psz_sdp_file != NULL ) FileSetup( p_stream );

    free( id );
}