#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {char* psz_name; int /*<<< orphan*/  out; TYPE_3__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {int i_width; int i_height; } ;
struct TYPE_11__ {TYPE_1__ video; } ;
struct TYPE_10__ {TYPE_6__ fmt; int /*<<< orphan*/  p_es; int /*<<< orphan*/  pts; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  DemuxControl ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 

__attribute__((used)) static int OpenDemux ( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys;

    p_demux->p_sys = NULL;

    /* Only when selected */
    if( *p_demux->psz_name == '\0' )
        return VLC_EGENERIC;

    msg_Dbg( p_demux, "Init Stat demux" );

    p_demux->pf_demux   = Demux;
    p_demux->pf_control = DemuxControl;

    p_demux->p_sys = p_sys = malloc( sizeof( demux_sys_t ) );
    if( !p_demux->p_sys )
        return VLC_ENOMEM;

    date_Init( &p_sys->pts, 1, 1 );
    date_Set( &p_sys->pts, VLC_TICK_0 );

    es_format_Init( &p_sys->fmt, VIDEO_ES, VLC_FOURCC('s','t','a','t') );
    p_sys->fmt.video.i_width = 720;
    p_sys->fmt.video.i_height= 480;

    p_sys->p_es = es_out_Add( p_demux->out, &p_sys->fmt );

    return VLC_SUCCESS;
}