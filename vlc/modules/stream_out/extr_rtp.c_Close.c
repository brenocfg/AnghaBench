#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_7__ {int i_es; struct TYPE_7__* psz_destination; struct TYPE_7__* psz_vod_session; struct TYPE_7__* psz_sdp_file; struct TYPE_7__* psz_sdp; scalar_t__ p_httpd_host; scalar_t__ p_httpd_file; int /*<<< orphan*/  lock_es; int /*<<< orphan*/  lock_ts; int /*<<< orphan*/  lock_sdp; int /*<<< orphan*/ * rtsp; scalar_t__ packet; int /*<<< orphan*/  p_grab; int /*<<< orphan*/ * es; scalar_t__ p_mux; } ;
typedef  TYPE_2__ sout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Del (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtspUnsetup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  httpd_FileDelete (scalar_t__) ; 
 int /*<<< orphan*/  httpd_HostDelete (scalar_t__) ; 
 int /*<<< orphan*/  sout_AccessOutDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sout_MuxDelete (scalar_t__) ; 
 int /*<<< orphan*/  unlink (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_stream_t     *p_stream = (sout_stream_t*)p_this;
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    if( p_sys->p_mux )
    {
        assert( p_sys->i_es <= 1 );

        sout_MuxDelete( p_sys->p_mux );
        if ( p_sys->i_es > 0 )
            Del( p_stream, p_sys->es[0] );
        sout_AccessOutDelete( p_sys->p_grab );

        if( p_sys->packet )
        {
            block_Release( p_sys->packet );
        }
    }

    if( p_sys->rtsp != NULL )
        RtspUnsetup( p_sys->rtsp );

    vlc_mutex_destroy( &p_sys->lock_sdp );
    vlc_mutex_destroy( &p_sys->lock_ts );
    vlc_mutex_destroy( &p_sys->lock_es );

    if( p_sys->p_httpd_file )
        httpd_FileDelete( p_sys->p_httpd_file );

    if( p_sys->p_httpd_host )
        httpd_HostDelete( p_sys->p_httpd_host );

    free( p_sys->psz_sdp );

    if( p_sys->psz_sdp_file != NULL )
    {
        unlink( p_sys->psz_sdp_file );
        free( p_sys->psz_sdp_file );
    }
    free( p_sys->psz_vod_session );
    free( p_sys->psz_destination );
    free( p_sys );
}