#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int vlc_fourcc_t ;
struct TYPE_16__ {int bitsPerPixel; int redShift; int greenShift; int blueShift; int redMax; int greenMax; int blueMax; } ;
struct TYPE_18__ {int width; int height; TYPE_1__ format; } ;
typedef  TYPE_3__ rfbClient ;
typedef  int /*<<< orphan*/  rfbBool ;
struct TYPE_17__ {int i_chroma; int i_visible_width; int i_width; int i_visible_height; int i_height; int i_frame_rate_base; int i_frame_rate; int i_bits_per_pixel; int i_rmask; int i_gmask; int i_bmask; int i_sar_num; int i_sar_den; } ;
struct TYPE_19__ {TYPE_2__ video; } ;
typedef  TYPE_4__ es_format_t ;
struct TYPE_20__ {int /*<<< orphan*/  out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_21__ {int i_framebuffersize; int f_fps; int /*<<< orphan*/ * es; TYPE_11__* p_block; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_15__ {int i_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DemuxThread ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetFormatAndEncodings (TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VIDEO_ES ; 
#define  VLC_CODEC_RGB16 130 
#define  VLC_CODEC_RGB24 129 
#define  VLC_CODEC_RGB32 128 
 int VLC_CODEC_RGB8 ; 
 TYPE_11__* block_Alloc (int) ; 
 TYPE_11__* block_Realloc (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rfbClientGetClientData (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rfbBool mallocFrameBufferHandler( rfbClient* p_client )
{
    vlc_fourcc_t i_chroma;
    demux_t *p_demux = (demux_t *) rfbClientGetClientData( p_client, DemuxThread );
    demux_sys_t *p_sys = p_demux->p_sys;

    if ( p_sys->es ) /* Source has changed resolution */
    {
        es_out_Del( p_demux->out, p_sys->es );
        p_sys->es = NULL;
    }

    int i_width = p_client->width;
    int i_height = p_client->height;
    int i_depth = p_client->format.bitsPerPixel;

    switch( i_depth )
    {
        case 8:
            i_chroma = VLC_CODEC_RGB8;
            break;
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

    switch( i_chroma )
    {
        case VLC_CODEC_RGB16:
            p_client->format.redShift   = 11;
            p_client->format.greenShift =  5;
            p_client->format.blueShift  =  0;
            p_client->format.redMax     = 0x1f;
            p_client->format.greenMax   = 0x3f;
            p_client->format.blueMax    = 0x1f;
            break;
        case VLC_CODEC_RGB24:
        case VLC_CODEC_RGB32:
            p_client->format.redShift   = 16;
            p_client->format.greenShift =  8;
            p_client->format.blueShift  =  0;
            p_client->format.redMax     = 0xff;
            p_client->format.greenMax   = 0xff;
            p_client->format.blueMax    = 0xff;
            break;
    }

    /* Set up framebuffer */
    p_sys->i_framebuffersize = i_width * i_height * i_depth / 8;

    /* Reuse unsent block */
    if ( p_sys->p_block )
        p_sys->p_block = block_Realloc( p_sys->p_block, 0, p_sys->i_framebuffersize );
    else
        p_sys->p_block = block_Alloc( p_sys->i_framebuffersize );

    if ( p_sys->p_block )
        p_sys->p_block->i_buffer = p_sys->i_framebuffersize;
    else
        return FALSE;

    /* Push our VNC config */
    SetFormatAndEncodings( p_client );

    /* Now init and fill es format */
    es_format_t fmt;
    es_format_Init( &fmt, VIDEO_ES, i_chroma );

    /* Fill input format */
    fmt.video.i_chroma = i_chroma;
    fmt.video.i_visible_width =
            fmt.video.i_width = i_width;

    fmt.video.i_visible_height =
            fmt.video.i_height = i_height;

    fmt.video.i_frame_rate_base = 1000;
    fmt.video.i_frame_rate = 1000 * p_sys->f_fps;

    fmt.video.i_bits_per_pixel = i_depth;
    fmt.video.i_rmask = p_client->format.redMax << p_client->format.redShift;
    fmt.video.i_gmask = p_client->format.greenMax << p_client->format.greenShift;
    fmt.video.i_bmask = p_client->format.blueMax << p_client->format.blueShift;

    fmt.video.i_sar_num = fmt.video.i_sar_den = 1;

    /* declare the new es */
    p_sys->es = es_out_Add( p_demux->out, &fmt );

    return TRUE;
}