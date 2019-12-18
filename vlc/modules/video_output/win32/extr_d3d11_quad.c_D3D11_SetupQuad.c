#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  video_orientation_t ;
struct TYPE_23__ {int i_visible_width; int i_width; float i_visible_height; float i_height; int space; int /*<<< orphan*/  primaries; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_24__ {int /*<<< orphan*/  primaries; TYPE_11__* pixelFormat; scalar_t__ luminance_peak; } ;
typedef  TYPE_4__ display_info_t ;
struct TYPE_21__ {int /*<<< orphan*/  context; int /*<<< orphan*/  formatTexture; } ;
struct TYPE_27__ {float LuminanceScale; double Opacity; double BoundaryX; double BoundaryY; float* WhitePoint; float* Colorspace; int /*<<< orphan*/  Primaries; } ;
struct TYPE_25__ {TYPE_11__* textureFormat; int /*<<< orphan*/  resourceCount; TYPE_2__* cropViewport; TYPE_1__ picSys; TYPE_7__ shaderConstants; } ;
typedef  TYPE_5__ d3d_quad_t ;
struct TYPE_26__ {int /*<<< orphan*/  d3dcontext; } ;
typedef  TYPE_6__ d3d11_device_t ;
struct TYPE_22__ {float MinDepth; float MaxDepth; } ;
struct TYPE_20__ {int bitsPerChannel; int /*<<< orphan*/  formatTexture; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_7__ PS_COLOR_TRANSFORM ;
typedef  float FLOAT ;

/* Variables and functions */
#define  COLOR_SPACE_BT2020 131 
#define  COLOR_SPACE_BT601 130 
#define  COLOR_SPACE_BT709 129 
#define  COLOR_SPACE_UNDEF 128 
 size_t D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  D3D11_UpdateQuadPosition (int /*<<< orphan*/ *,TYPE_6__*,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DxgiResourceCount (TYPE_11__*) ; 
 float GetFormatLuminance (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  GetPrimariesTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_AddRef (int /*<<< orphan*/ ) ; 
 int IsRGBShader (TYPE_11__*) ; 
 int /*<<< orphan*/  PS_CONST_COLORSPACE ; 
 int /*<<< orphan*/  PS_CONST_LUMI_BOUNDS ; 
 int /*<<< orphan*/  ShaderUpdateConstants (int /*<<< orphan*/ *,TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int) ; 

int D3D11_SetupQuad(vlc_object_t *o, d3d11_device_t *d3d_dev, const video_format_t *fmt, d3d_quad_t *quad,
                    const display_info_t *displayFormat, const RECT *output,
                    video_orientation_t orientation)
{
    const bool RGB_shader = IsRGBShader(quad->textureFormat);

    quad->shaderConstants.LuminanceScale = (float)displayFormat->luminance_peak / GetFormatLuminance(o, fmt);

    /* pixel shader constant buffer */
    quad->shaderConstants.Opacity = 1.0;
    if (fmt->i_visible_width == fmt->i_width)
        quad->shaderConstants.BoundaryX = 1.0; /* let texture clamping happen */
    else
        quad->shaderConstants.BoundaryX = (FLOAT) (fmt->i_visible_width - 1) / fmt->i_width;
    if (fmt->i_visible_height == fmt->i_height)
        quad->shaderConstants.BoundaryY = 1.0; /* let texture clamping happen */
    else
        quad->shaderConstants.BoundaryY = (FLOAT) (fmt->i_visible_height - 1) / fmt->i_height;

    ShaderUpdateConstants(o, d3d_dev, quad, PS_CONST_LUMI_BOUNDS, &quad->shaderConstants);

    FLOAT itu_black_level = 0.f;
    FLOAT itu_achromacy   = 0.f;
    if (!RGB_shader)
    {
        switch (quad->textureFormat->bitsPerChannel)
        {
        case 8:
            /* Rec. ITU-R BT.709-6 ¶4.6 */
            itu_black_level  =              16.f / 255.f;
            itu_achromacy    =             128.f / 255.f;
            break;
        case 10:
            /* Rec. ITU-R BT.709-6 ¶4.6 */
            itu_black_level  =              64.f / 1023.f;
            itu_achromacy    =             512.f / 1023.f;
            break;
        case 12:
            /* Rec. ITU-R BT.2020-2 Table 5 */
            itu_black_level  =               256.f / 4095.f;
            itu_achromacy    =              2048.f / 4095.f;
            break;
        default:
            /* unknown bitdepth, use approximation for infinite bit depth */
            itu_black_level  =              16.f / 256.f;
            itu_achromacy    =             128.f / 256.f;
            break;
        }
    }

    static const FLOAT IDENTITY_4X4[4 * 4] = {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };

    /* matrices for studio range */
    /* see https://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.601_conversion, in studio range */
    static const FLOAT COLORSPACE_BT601_YUV_TO_FULL_RGBA[4*4] = {
        1.164383561643836f,                 0.f,  1.596026785714286f, 0.f,
        1.164383561643836f, -0.391762290094914f, -0.812967647237771f, 0.f,
        1.164383561643836f,  2.017232142857142f,                 0.f, 0.f,
                       0.f,                 0.f,                 0.f, 1.f,
    };

    static const FLOAT COLORSPACE_FULL_RGBA_TO_BT601_YUV[4*4] = {
        0.299000f,  0.587000f,  0.114000f, 0.f,
       -0.168736f, -0.331264f,  0.500000f, 0.f,
        0.500000f, -0.418688f, -0.081312f, 0.f,
              0.f,        0.f,        0.f, 1.f,
    };

    /* see https://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.709_conversion, in studio range */
    static const FLOAT COLORSPACE_BT709_YUV_TO_FULL_RGBA[4*4] = {
        1.164383561643836f,                 0.f,  1.792741071428571f, 0.f,
        1.164383561643836f, -0.213248614273730f, -0.532909328559444f, 0.f,
        1.164383561643836f,  2.112401785714286f,                 0.f, 0.f,
                       0.f,                 0.f,                 0.f, 1.f,
    };
    /* see https://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.2020_conversion, in studio range */
    static const FLOAT COLORSPACE_BT2020_YUV_TO_FULL_RGBA[4*4] = {
        1.164383561643836f,  0.000000000000f,  1.678674107143f, 0.f,
        1.164383561643836f, -0.127007098661f, -0.440987687946f, 0.f,
        1.164383561643836f,  2.141772321429f,  0.000000000000f, 0.f,
                       0.f,              0.f,              0.f, 1.f,
    };

    PS_COLOR_TRANSFORM colorspace;

    memcpy(colorspace.WhitePoint, IDENTITY_4X4, sizeof(colorspace.WhitePoint));

    const FLOAT *ppColorspace;
    if (!IsRGBShader(displayFormat->pixelFormat))
    {
        if (!RGB_shader)
            ppColorspace = IDENTITY_4X4;
        else
        {
            ppColorspace = COLORSPACE_FULL_RGBA_TO_BT601_YUV;
            colorspace.WhitePoint[0*4 + 3] = -itu_black_level;
            colorspace.WhitePoint[1*4 + 3] = itu_achromacy;
            colorspace.WhitePoint[2*4 + 3] = itu_achromacy;
        }
    }
    else
    {
        if (RGB_shader)
            ppColorspace = IDENTITY_4X4;
        else {
            switch (fmt->space){
                case COLOR_SPACE_BT709:
                    ppColorspace = COLORSPACE_BT709_YUV_TO_FULL_RGBA;
                    break;
                case COLOR_SPACE_BT2020:
                    ppColorspace = COLORSPACE_BT2020_YUV_TO_FULL_RGBA;
                    break;
                case COLOR_SPACE_BT601:
                    ppColorspace = COLORSPACE_BT601_YUV_TO_FULL_RGBA;
                    break;
                default:
                case COLOR_SPACE_UNDEF:
                    if( fmt->i_height > 576 )
                        ppColorspace = COLORSPACE_BT709_YUV_TO_FULL_RGBA;
                    else
                        ppColorspace = COLORSPACE_BT601_YUV_TO_FULL_RGBA;
                    break;
            }
            /* all matrices work in studio range and output in full range */
            colorspace.WhitePoint[0*4 + 3] = -itu_black_level;
            colorspace.WhitePoint[1*4 + 3] = -itu_achromacy;
            colorspace.WhitePoint[2*4 + 3] = -itu_achromacy;
        }
    }

    memcpy(colorspace.Colorspace, ppColorspace, sizeof(colorspace.Colorspace));

    if (fmt->primaries != displayFormat->primaries)
    {
        GetPrimariesTransform(colorspace.Primaries, fmt->primaries,
                              displayFormat->primaries);
    }

    ShaderUpdateConstants(o, d3d_dev, quad, PS_CONST_COLORSPACE, &colorspace);


    quad->picSys.formatTexture = quad->textureFormat->formatTexture;
    quad->picSys.context = d3d_dev->d3dcontext;
    ID3D11DeviceContext_AddRef(quad->picSys.context);

    if (!D3D11_UpdateQuadPosition(o, d3d_dev, quad, output, orientation))
        return VLC_EGENERIC;

    for (size_t i=0; i<D3D11_MAX_SHADER_VIEW; i++)
    {
        quad->cropViewport[i].MinDepth = 0.0f;
        quad->cropViewport[i].MaxDepth = 1.0f;
    }
    quad->resourceCount = DxgiResourceCount(quad->textureFormat);

    return VLC_SUCCESS;
}