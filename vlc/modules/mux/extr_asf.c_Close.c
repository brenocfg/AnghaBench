#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_access; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_11__ {struct TYPE_11__* psz_rating; struct TYPE_11__* psz_comment; struct TYPE_11__* psz_copyright; struct TYPE_11__* psz_author; struct TYPE_11__* psz_title; int /*<<< orphan*/  tracks; int /*<<< orphan*/  fmt; struct TYPE_11__* p_extra; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
typedef  int /*<<< orphan*/  block_t ;
typedef  TYPE_2__ asf_track_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/ * asf_header_create (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * asf_packet_flush (TYPE_1__*) ; 
 int /*<<< orphan*/ * asf_stream_end_create (TYPE_1__*) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 scalar_t__ sout_AccessOutSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_mux_t     *p_mux = (sout_mux_t*)p_this;
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    block_t  *out;

    msg_Dbg( p_mux, "Asf muxer closed" );

    /* Flush last packet if any */
    if( (out = asf_packet_flush( p_mux ) ) )
    {
        sout_AccessOutWrite( p_mux->p_access, out );
    }

    if( ( out = asf_stream_end_create( p_mux ) ) )
    {
        sout_AccessOutWrite( p_mux->p_access, out );
    }

    /* rewrite header */
    if( sout_AccessOutSeek( p_mux->p_access, 0 ) == VLC_SUCCESS )
    {
        out = asf_header_create( p_mux, false );
        sout_AccessOutWrite( p_mux->p_access, out );
    }


    for( size_t i = 0; i < vlc_array_count( &p_sys->tracks ); i++ )
    {
        asf_track_t *track = vlc_array_item_at_index( &p_sys->tracks, i );
        free( track->p_extra );
        es_format_Clean( &track->fmt );
        free( track );
    }

    vlc_array_clear( &p_sys->tracks );
    free( p_sys->psz_title );
    free( p_sys->psz_author );
    free( p_sys->psz_copyright );
    free( p_sys->psz_comment );
    free( p_sys->psz_rating );
    free( p_sys );
}