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
struct block_extension_t {int dummy; } ;
struct TYPE_10__ {int i_frame_rate; int i_frame_rate_base; int i_width; int i_visible_width; int i_height; int i_visible_height; int i_sar_num; int i_sar_den; } ;
struct TYPE_11__ {TYPE_1__ video; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_13__ {int i_standard; int i_frame_rate; int i_frame_rate_base; int i_width; int i_height; int i_aspect; int i_vblock_size; int /*<<< orphan*/  p_es_video; int /*<<< orphan*/  i_id_video; int /*<<< orphan*/  i_incr; int /*<<< orphan*/  i_next_vdate; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
#define  SDIVIDEO_CTL_BT_601_576I_50HZ 135 
#define  SDIVIDEO_CTL_SMPTE_274M_1080I_50HZ 134 
#define  SDIVIDEO_CTL_SMPTE_274M_1080I_59_94HZ 133 
#define  SDIVIDEO_CTL_SMPTE_274M_1080I_60HZ 132 
#define  SDIVIDEO_CTL_SMPTE_274M_1080PSF_25HZ 131 
#define  SDIVIDEO_CTL_SMPTE_295M_1080I_50HZ 130 
#define  SDIVIDEO_CTL_SMPTE_296M_720P_50HZ 129 
#define  SDIVIDEO_CTL_SMPTE_296M_720P_60HZ 128 
 int /*<<< orphan*/  START_DATE ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_I420 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int VOUT_ASPECT_FACTOR ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (int,int) ; 

__attribute__((used)) static int InitVideo( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    es_format_t fmt;

    msg_Dbg( p_demux, "found standard %d", p_sys->i_standard );
    switch ( p_sys->i_standard )
    {
    case SDIVIDEO_CTL_BT_601_576I_50HZ:
        /* PAL */
        p_sys->i_frame_rate      = 25;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_width           = 720;
        p_sys->i_height          = 576;
        p_sys->i_aspect          = 4 * VOUT_ASPECT_FACTOR / 3;
        break;

    case SDIVIDEO_CTL_SMPTE_296M_720P_50HZ:
        p_sys->i_frame_rate      = 50;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_width           = 1280;
        p_sys->i_height          = 720;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        break;

    case SDIVIDEO_CTL_SMPTE_296M_720P_60HZ:
        p_sys->i_frame_rate      = 60;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_width           = 1280;
        p_sys->i_height          = 720;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        break;

    case SDIVIDEO_CTL_SMPTE_295M_1080I_50HZ:
    case SDIVIDEO_CTL_SMPTE_274M_1080I_50HZ:
    case SDIVIDEO_CTL_SMPTE_274M_1080PSF_25HZ:
        /* 1080i50 or 1080p25 */
        p_sys->i_frame_rate      = 25;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_width           = 1920;
        p_sys->i_height          = 1080;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        break;

    case SDIVIDEO_CTL_SMPTE_274M_1080I_59_94HZ:
        p_sys->i_frame_rate      = 30000;
        p_sys->i_frame_rate_base = 1001;
        p_sys->i_width           = 1920;
        p_sys->i_height          = 1080;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        break;

    case SDIVIDEO_CTL_SMPTE_274M_1080I_60HZ:
        p_sys->i_frame_rate      = 30;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_width           = 1920;
        p_sys->i_height          = 1080;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        break;

    default:
        msg_Err( p_demux, "unsupported standard %d", p_sys->i_standard );
        return VLC_EGENERIC;
    }

    p_sys->i_next_vdate = START_DATE;
    p_sys->i_incr = vlc_tick_from_samples(p_sys->i_frame_rate_base, p_sys->i_frame_rate);
    p_sys->i_vblock_size = p_sys->i_width * p_sys->i_height * 3 / 2
                            + sizeof(struct block_extension_t);

    /* Video ES */
    es_format_Init( &fmt, VIDEO_ES, VLC_CODEC_I420 );
    fmt.i_id                    = p_sys->i_id_video;
    fmt.video.i_frame_rate      = p_sys->i_frame_rate;
    fmt.video.i_frame_rate_base = p_sys->i_frame_rate_base;
    fmt.video.i_width           = fmt.video.i_visible_width = p_sys->i_width;
    fmt.video.i_height          = fmt.video.i_visible_height = p_sys->i_height;
    fmt.video.i_sar_num         = p_sys->i_aspect * fmt.video.i_height
                                  / fmt.video.i_width;
    fmt.video.i_sar_den         = VOUT_ASPECT_FACTOR;
    p_sys->p_es_video           = es_out_Add( p_demux->out, &fmt );

    return VLC_SUCCESS;
}