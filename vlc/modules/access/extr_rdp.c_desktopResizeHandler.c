#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* p_demux; } ;
typedef  TYPE_3__ vlcrdp_context_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_14__ {int bytesPerPixel; int width; int height; } ;
typedef  TYPE_4__ rdpGdi ;
struct TYPE_15__ {TYPE_4__* gdi; } ;
typedef  TYPE_5__ rdpContext ;
struct TYPE_11__ {int i_visible_width; int i_width; int i_visible_height; int i_height; int i_frame_rate_base; int i_frame_rate; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_16__ {TYPE_1__ video; } ;
typedef  TYPE_6__ es_format_t ;
struct TYPE_17__ {int f_fps; int i_framebuffersize; int /*<<< orphan*/ * es; scalar_t__ p_block; } ;
typedef  TYPE_7__ demux_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_7__* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_RGB16 ; 
 int /*<<< orphan*/  VLC_CODEC_RGB24 ; 
 int /*<<< orphan*/  VLC_CODEC_RGB32 ; 
 scalar_t__ block_Alloc (int) ; 
 scalar_t__ block_Realloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void desktopResizeHandler( rdpContext *p_context )
{
    vlcrdp_context_t * p_vlccontext = (vlcrdp_context_t *) p_context;
    demux_sys_t *p_sys = p_vlccontext->p_demux->p_sys;
    rdpGdi *p_gdi = p_context->gdi;

    if ( p_sys->es )
    {
        es_out_Del( p_vlccontext->p_demux->out, p_sys->es );
        p_sys->es = NULL;
    }

    /* Now init and fill es format */
    vlc_fourcc_t i_chroma;
    switch( p_gdi->bytesPerPixel )
    {
        default:
        case 16:
            i_chroma = VLC_CODEC_RGB16;
            break;
        case 24:
            i_chroma = VLC_CODEC_RGB24;
            break;
        case 32:
            i_chroma = VLC_CODEC_RGB32;
            break;
    }
    es_format_t fmt;
    es_format_Init( &fmt, VIDEO_ES, i_chroma );

    fmt.video.i_chroma = i_chroma;
    fmt.video.i_visible_width =
    fmt.video.i_width = p_gdi->width;
    fmt.video.i_visible_height =
    fmt.video.i_height = p_gdi->height;
    fmt.video.i_frame_rate_base = 1000;
    fmt.video.i_frame_rate = 1000 * p_sys->f_fps;
    p_sys->i_framebuffersize = p_gdi->width * p_gdi->height * p_gdi->bytesPerPixel;

    if ( p_sys->p_block )
        p_sys->p_block = block_Realloc( p_sys->p_block, 0, p_sys->i_framebuffersize );
    else
        p_sys->p_block = block_Alloc( p_sys->i_framebuffersize );

    p_sys->es = es_out_Add( p_vlccontext->p_demux->out, &fmt );
}