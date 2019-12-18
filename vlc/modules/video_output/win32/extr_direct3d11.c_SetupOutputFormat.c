#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_7__* sys; } ;
typedef  TYPE_6__ vout_display_t ;
struct TYPE_28__ {void* textureFormat; } ;
struct TYPE_27__ {TYPE_10__* textureFormat; } ;
struct TYPE_30__ {TYPE_5__ regionQuad; TYPE_4__ picQuad; } ;
typedef  TYPE_7__ vout_display_sys_t ;
struct TYPE_31__ {int pixel_bits; int plane_count; int pixel_size; TYPE_3__* p; } ;
typedef  TYPE_8__ vlc_chroma_description_t ;
struct TYPE_32__ {scalar_t__ i_chroma; } ;
typedef  TYPE_9__ video_format_t ;
typedef  int uint8_t ;
struct TYPE_23__ {int /*<<< orphan*/  formatTexture; scalar_t__ fourcc; int /*<<< orphan*/  name; } ;
typedef  TYPE_10__ d3d_format_t ;
struct TYPE_25__ {int den; } ;
struct TYPE_24__ {int den; } ;
struct TYPE_26__ {TYPE_2__ h; TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  DxgiFormatMask (int /*<<< orphan*/ ,TYPE_9__*) ; 
 void* GetBlendableFormat (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* GetDirectDecoderFormat (TYPE_6__*,scalar_t__) ; 
 TYPE_10__* GetDirectRenderingFormat (TYPE_6__*,scalar_t__) ; 
 void* GetDisplayFormatByDepth (TYPE_6__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  VLC_CODEC_BGRA ; 
#define  VLC_CODEC_D3D11_OPAQUE 134 
#define  VLC_CODEC_D3D11_OPAQUE_10B 133 
#define  VLC_CODEC_D3D11_OPAQUE_BGRA 132 
#define  VLC_CODEC_D3D11_OPAQUE_RGBA 131 
#define  VLC_CODEC_NVDEC_OPAQUE 130 
#define  VLC_CODEC_NVDEC_OPAQUE_10B 129 
#define  VLC_CODEC_NVDEC_OPAQUE_16B 128 
 int /*<<< orphan*/  VLC_CODEC_RGBA ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ is_d3d11_opaque (scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_6__*,char*) ; 
 TYPE_8__* vlc_fourcc_GetChromaDescription (scalar_t__) ; 
 int /*<<< orphan*/  vlc_fourcc_IsYUV (scalar_t__) ; 

__attribute__((used)) static int SetupOutputFormat(vout_display_t *vd, video_format_t *fmt)
{
    vout_display_sys_t *sys = vd->sys;

    // look for the requested pixel format first
    sys->picQuad.textureFormat = GetDirectRenderingFormat(vd, fmt->i_chroma);

    // look for any pixel format that we can handle with enough pixels per channel
    const d3d_format_t *decoder_format = NULL;
    if ( !sys->picQuad.textureFormat )
    {
        uint8_t bits_per_channel;
        uint8_t widthDenominator, heightDenominator;
        switch (fmt->i_chroma)
        {
        case VLC_CODEC_D3D11_OPAQUE:
        case VLC_CODEC_NVDEC_OPAQUE:
            bits_per_channel = 8;
            widthDenominator = heightDenominator = 2;
            break;
        case VLC_CODEC_D3D11_OPAQUE_RGBA:
        case VLC_CODEC_D3D11_OPAQUE_BGRA:
            bits_per_channel = 8;
            widthDenominator = heightDenominator = 1;
            break;
        case VLC_CODEC_D3D11_OPAQUE_10B:
        case VLC_CODEC_NVDEC_OPAQUE_10B:
            bits_per_channel = 10;
            widthDenominator = heightDenominator = 2;
            break;
        case VLC_CODEC_NVDEC_OPAQUE_16B:
            bits_per_channel = 16;
            widthDenominator = heightDenominator = 2;
            break;
        default:
            {
                const vlc_chroma_description_t *p_format = vlc_fourcc_GetChromaDescription(fmt->i_chroma);
                if (p_format == NULL)
                {
                    bits_per_channel = 8;
                    widthDenominator = heightDenominator = 2;
                }
                else
                {
                    bits_per_channel = p_format->pixel_bits == 0 ? 8 : p_format->pixel_bits /
                                                                   (p_format->plane_count==1 ? p_format->pixel_size : 1);
                    widthDenominator = heightDenominator = 1;
                    for (size_t i=0; i<p_format->plane_count; i++)
                    {
                        if (widthDenominator < p_format->p[i].w.den)
                            widthDenominator = p_format->p[i].w.den;
                        if (heightDenominator < p_format->p[i].h.den)
                            heightDenominator = p_format->p[1].h.den;
                    }
                }
            }
            break;
        }

        /* look for a decoder format that can be decoded but not used in shaders */
        if ( is_d3d11_opaque(fmt->i_chroma) )
            decoder_format = GetDirectDecoderFormat(vd, fmt->i_chroma);
        else
            decoder_format = sys->picQuad.textureFormat;

        bool is_rgb = !vlc_fourcc_IsYUV(fmt->i_chroma);
        sys->picQuad.textureFormat = GetDisplayFormatByDepth(vd, bits_per_channel,
                                                             widthDenominator, heightDenominator,
                                                             decoder_format!=NULL, is_rgb);
        if (!sys->picQuad.textureFormat && is_rgb)
            sys->picQuad.textureFormat = GetDisplayFormatByDepth(vd, bits_per_channel,
                                                                 widthDenominator, heightDenominator,
                                                                 decoder_format!=NULL, false);
    }

    // look for any pixel format that we can handle
    if ( !sys->picQuad.textureFormat )
        sys->picQuad.textureFormat = GetDisplayFormatByDepth(vd, 0, 0, 0, false, false);

    if ( !sys->picQuad.textureFormat )
    {
       msg_Err(vd, "Could not get a suitable texture pixel format");
       return VLC_EGENERIC;
    }

    msg_Dbg( vd, "Using pixel format %s for chroma %4.4s", sys->picQuad.textureFormat->name,
                 (char *)&fmt->i_chroma );

    fmt->i_chroma = decoder_format ? decoder_format->fourcc : sys->picQuad.textureFormat->fourcc;
    DxgiFormatMask( sys->picQuad.textureFormat->formatTexture, fmt );

    /* check the region pixel format */
    sys->regionQuad.textureFormat = GetBlendableFormat(vd, VLC_CODEC_RGBA);
    if (!sys->regionQuad.textureFormat)
        sys->regionQuad.textureFormat = GetBlendableFormat(vd, VLC_CODEC_BGRA);

    return VLC_SUCCESS;
}