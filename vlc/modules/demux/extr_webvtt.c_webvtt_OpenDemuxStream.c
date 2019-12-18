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
typedef  int /*<<< orphan*/  es_format_t ;
struct TYPE_6__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {int /*<<< orphan*/ * es; int /*<<< orphan*/  p_streamparser; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ControlStream ; 
 int /*<<< orphan*/  DemuxStream ; 
 int ProbeWEBVTT (TYPE_1__*) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  StreamParserCueDoneHandler ; 
 int /*<<< orphan*/  StreamParserGetCueHandler ; 
 int /*<<< orphan*/  VLC_CODEC_WEBVTT ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webvtt_CloseDemux (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  webvtt_text_parser_New (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int webvtt_OpenDemuxStream ( vlc_object_t *p_this )
{
    demux_t        *p_demux = (demux_t*)p_this;
    demux_sys_t    *p_sys;

    int i_ret = ProbeWEBVTT( p_demux );
    if( i_ret != VLC_SUCCESS )
        return i_ret;

    p_demux->pf_demux = DemuxStream;
    p_demux->pf_control = ControlStream;

    p_demux->p_sys = p_sys = calloc( 1, sizeof( demux_sys_t ) );
    if( p_sys == NULL )
        return VLC_ENOMEM;

    p_sys->p_streamparser = webvtt_text_parser_New( p_demux,
                                          StreamParserGetCueHandler,
                                          StreamParserCueDoneHandler,
                                          NULL );
    if( !p_sys->p_streamparser )
    {
        webvtt_CloseDemux( p_this );
        return VLC_EGENERIC;
    }

    es_format_t fmt;
    es_format_Init( &fmt, SPU_ES, VLC_CODEC_WEBVTT );
    p_sys->es = es_out_Add( p_demux->out, &fmt );
    es_format_Clean( &fmt );
    if( p_sys->es == NULL )
    {
        webvtt_CloseDemux( p_this );
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}