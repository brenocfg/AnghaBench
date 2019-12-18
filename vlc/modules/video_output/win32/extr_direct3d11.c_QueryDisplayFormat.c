#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_16__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_17__ {TYPE_1__ display; } ;
struct TYPE_18__ {TYPE_2__ vdcfg; } ;
struct TYPE_20__ {int /*<<< orphan*/  outside_opaque; int /*<<< orphan*/  (* updateOutputCb ) (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ;TYPE_3__ area; } ;
typedef  TYPE_5__ vout_display_sys_t ;
struct TYPE_21__ {int pixel_bits; int plane_count; int pixel_size; } ;
typedef  TYPE_6__ vlc_chroma_description_t ;
struct TYPE_22__ {int i_chroma; scalar_t__ color_range; scalar_t__ transfer; scalar_t__ space; scalar_t__ primaries; } ;
typedef  TYPE_7__ video_format_t ;
typedef  scalar_t__ libvlc_video_transfer_func_t ;
typedef  int /*<<< orphan*/  libvlc_video_output_cfg_t ;
struct TYPE_23__ {int bitdepth; int full_range; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ transfer; scalar_t__ colorspace; scalar_t__ primaries; } ;
typedef  TYPE_8__ libvlc_video_direct3d_cfg_t ;
typedef  scalar_t__ libvlc_video_color_space_t ;
typedef  scalar_t__ libvlc_video_color_primaries_t ;

/* Variables and functions */
 scalar_t__ COLOR_RANGE_FULL ; 
 int UpdateDisplayFormat (TYPE_4__*,int /*<<< orphan*/ *,TYPE_7__ const*) ; 
#define  VLC_CODEC_D3D11_OPAQUE 131 
#define  VLC_CODEC_D3D11_OPAQUE_10B 130 
#define  VLC_CODEC_D3D11_OPAQUE_BGRA 129 
#define  VLC_CODEC_D3D11_OPAQUE_RGBA 128 
 int VLC_EGENERIC ; 
 scalar_t__ is_d3d11_opaque (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* vlc_fourcc_GetChromaDescription (int) ; 
 scalar_t__ vlc_fourcc_IsYUV (int) ; 

__attribute__((used)) static int QueryDisplayFormat(vout_display_t *vd, const video_format_t *fmt)
{
    vout_display_sys_t *sys = vd->sys;
    libvlc_video_direct3d_cfg_t cfg;

    cfg.width  = sys->area.vdcfg.display.width;
    cfg.height = sys->area.vdcfg.display.height;

    switch (fmt->i_chroma)
    {
    case VLC_CODEC_D3D11_OPAQUE:
        cfg.bitdepth = 8;
        break;
    case VLC_CODEC_D3D11_OPAQUE_RGBA:
    case VLC_CODEC_D3D11_OPAQUE_BGRA:
        cfg.bitdepth = 8;
        break;
    case VLC_CODEC_D3D11_OPAQUE_10B:
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
    cfg.full_range = fmt->color_range == COLOR_RANGE_FULL ||
                     /* the YUV->RGB conversion already output full range */
                     is_d3d11_opaque(fmt->i_chroma) ||
                     vlc_fourcc_IsYUV(fmt->i_chroma);
    cfg.primaries  = (libvlc_video_color_primaries_t) fmt->primaries;
    cfg.colorspace = (libvlc_video_color_space_t)     fmt->space;
    cfg.transfer   = (libvlc_video_transfer_func_t)   fmt->transfer;

    libvlc_video_output_cfg_t out;
    if (!sys->updateOutputCb( sys->outside_opaque, &cfg, &out ))
    {
        msg_Err(vd, "Failed to set format %dx%d %d bits on output", cfg.width, cfg.height, cfg.bitdepth);
        return VLC_EGENERIC;
    }

    return UpdateDisplayFormat(vd, &out, fmt);
}