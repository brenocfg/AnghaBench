#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_6__* sys; } ;
typedef  TYPE_5__ vout_display_t ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_16__ {TYPE_1__ display; } ;
struct TYPE_17__ {TYPE_2__ vdcfg; } ;
struct TYPE_20__ {int /*<<< orphan*/  outside_opaque; int /*<<< orphan*/  (* updateOutputCb ) (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ;TYPE_4__ d3d_dev; TYPE_3__ area; } ;
typedef  TYPE_6__ vout_display_sys_t ;
struct TYPE_21__ {int pixel_bits; int plane_count; int pixel_size; } ;
typedef  TYPE_7__ vlc_chroma_description_t ;
struct TYPE_22__ {int i_chroma; scalar_t__ color_range; int /*<<< orphan*/  transfer; int /*<<< orphan*/  space; int /*<<< orphan*/  primaries; } ;
typedef  TYPE_8__ video_format_t ;
typedef  int /*<<< orphan*/  libvlc_video_output_cfg_t ;
struct TYPE_23__ {int bitdepth; int full_range; int /*<<< orphan*/  device; int /*<<< orphan*/  transfer; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  primaries; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_9__ libvlc_video_direct3d_cfg_t ;

/* Variables and functions */
 scalar_t__ COLOR_RANGE_FULL ; 
#define  VLC_CODEC_D3D9_OPAQUE 129 
#define  VLC_CODEC_D3D9_OPAQUE_10B 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_7__* vlc_fourcc_GetChromaDescription (int) ; 

__attribute__((used)) static int UpdateOutput(vout_display_t *vd, const video_format_t *fmt)
{
    vout_display_sys_t *sys = vd->sys;
    libvlc_video_direct3d_cfg_t cfg;
    cfg.width  = sys->area.vdcfg.display.width;
    cfg.height = sys->area.vdcfg.display.height;

    switch (fmt->i_chroma)
    {
    case VLC_CODEC_D3D9_OPAQUE:
        cfg.bitdepth = 8;
        break;
    case VLC_CODEC_D3D9_OPAQUE_10B:
        cfg.bitdepth = 10;
        break;
    default:
        {
            const vlc_chroma_description_t *p_format = vlc_fourcc_GetChromaDescription(fmt->i_chroma);
            if (p_format == NULL)
            {
                cfg.bitdepth = 8;
            }
            else
            {
                cfg.bitdepth = p_format->pixel_bits == 0 ? 8 : p_format->pixel_bits /
                                                               (p_format->plane_count==1 ? p_format->pixel_size : 1);
            }
        }
        break;
    }

    cfg.full_range = fmt->color_range == COLOR_RANGE_FULL;
    cfg.primaries  = fmt->primaries;
    cfg.colorspace = fmt->space;
    cfg.transfer   = fmt->transfer;

    cfg.device = sys->d3d_dev.dev;

    libvlc_video_output_cfg_t out;
    if (!sys->updateOutputCb( sys->outside_opaque, &cfg, &out ))
    {
        msg_Err(vd, "Failed to set the external render size");
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}