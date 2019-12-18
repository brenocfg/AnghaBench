#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {TYPE_3__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  out; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_9__ {int i_width; int i_height; int i_visible_width; int i_visible_height; } ;
struct TYPE_12__ {TYPE_1__ video; } ;
struct TYPE_11__ {int /*<<< orphan*/  pts; int /*<<< orphan*/ * p_es; TYPE_5__ fmt; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDG_FRAME_RATE ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_CDG ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_IsForced (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  demux_IsPathExtension (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_3__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Open( vlc_object_t * p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;

    /* Identify cdg file by extension, as there is no simple way to
     * detect it */
    if( !demux_IsPathExtension( p_demux, ".cdg" ) && !demux_IsForced( p_demux, "cdg" ) )
        return VLC_EGENERIC;

    /* CDG file size has to be multiple of CDG_FRAME_SIZE (it works even
     * if size is unknown ie 0) */
//    if( (stream_Size( p_demux->s ) % CDG_FRAME_SIZE) != 0 )
//    {
//        msg_Err( p_demux, "Reject CDG file based on its size" );
//        return VLC_EGENERIC;
//    }

    demux_sys_t *p_sys = vlc_obj_malloc( p_this, sizeof (*p_sys) );
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    es_format_Init( &p_sys->fmt, VIDEO_ES, VLC_CODEC_CDG );
    p_sys->fmt.video.i_width  = 300-2*6;
    p_sys->fmt.video.i_height = 216-2*12 ;
    p_sys->fmt.video.i_visible_width = p_sys->fmt.video.i_width;
    p_sys->fmt.video.i_visible_height = p_sys->fmt.video.i_height;

    p_sys->p_es = es_out_Add( p_demux->out, &p_sys->fmt );
    if( unlikely(p_sys->p_es == NULL) )
        return VLC_ENOMEM;

    /* There is CDG_FRAME_RATE frames per second */
    date_Init( &p_sys->pts, CDG_FRAME_RATE, 1 );
    date_Set( &p_sys->pts, VLC_TICK_0 );

    p_demux->pf_demux   = Demux;
    p_demux->pf_control = Control;
    p_demux->p_sys      = p_sys;
    return VLC_SUCCESS;
}