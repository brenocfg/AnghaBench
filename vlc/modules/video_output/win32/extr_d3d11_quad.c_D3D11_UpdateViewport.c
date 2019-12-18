#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* cropViewport; TYPE_1__* textureFormat; } ;
typedef  TYPE_3__ d3d_quad_t ;
struct TYPE_14__ {int const formatTexture; } ;
typedef  TYPE_4__ d3d_format_t ;
struct TYPE_15__ {int left; int top; } ;
struct TYPE_12__ {int TopLeftX; int TopLeftY; int Width; int Height; } ;
struct TYPE_11__ {int formatTexture; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_5__ RECT ;
typedef  int LONG ;

/* Variables and functions */
#define  DXGI_FORMAT_AYUV 141 
#define  DXGI_FORMAT_B5G6R5_UNORM 140 
#define  DXGI_FORMAT_B8G8R8A8_UNORM 139 
#define  DXGI_FORMAT_B8G8R8X8_UNORM 138 
#define  DXGI_FORMAT_NV12 137 
#define  DXGI_FORMAT_P010 136 
#define  DXGI_FORMAT_R10G10B10A2_UNORM 135 
#define  DXGI_FORMAT_R16G16B16A16_UNORM 134 
#define  DXGI_FORMAT_R8G8B8A8_UNORM 133 
#define  DXGI_FORMAT_UNKNOWN 132 
#define  DXGI_FORMAT_YUY2 131 
 int RECTHeight (TYPE_5__ const) ; 
 int RECTWidth (TYPE_5__ const) ; 
#define  VLC_CODEC_I420 130 
#define  VLC_CODEC_I420_10L 129 
#define  VLC_CODEC_YUVA 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

void D3D11_UpdateViewport(d3d_quad_t *quad, const RECT *rect, const d3d_format_t *display)
{
    LONG srcAreaWidth, srcAreaHeight;

    srcAreaWidth  = RECTWidth(*rect);
    srcAreaHeight = RECTHeight(*rect);

    quad->cropViewport[0].TopLeftX = rect->left;
    quad->cropViewport[0].TopLeftY = rect->top;
    quad->cropViewport[0].Width    = srcAreaWidth;
    quad->cropViewport[0].Height   = srcAreaHeight;

    switch ( quad->textureFormat->formatTexture )
    {
    case DXGI_FORMAT_NV12:
    case DXGI_FORMAT_P010:
        quad->cropViewport[1].TopLeftX = rect->left / 2;
        quad->cropViewport[1].TopLeftY = rect->top / 2;
        quad->cropViewport[1].Width    = srcAreaWidth / 2;
        quad->cropViewport[1].Height   = srcAreaHeight / 2;
        break;
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM:
    case DXGI_FORMAT_B5G6R5_UNORM:
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_R16G16B16A16_UNORM:
    case DXGI_FORMAT_YUY2:
    case DXGI_FORMAT_AYUV:
        if ( display->formatTexture == DXGI_FORMAT_NV12 ||
             display->formatTexture == DXGI_FORMAT_P010 )
        {
            quad->cropViewport[1].TopLeftX = rect->left / 2;
            quad->cropViewport[1].TopLeftY = rect->top / 2;
            quad->cropViewport[1].Width    = srcAreaWidth / 2;
            quad->cropViewport[1].Height   = srcAreaHeight / 2;
        }
        break;
    case DXGI_FORMAT_UNKNOWN:
        switch ( quad->textureFormat->fourcc )
        {
        case VLC_CODEC_YUVA:
            if ( display->formatTexture != DXGI_FORMAT_NV12 &&
                 display->formatTexture != DXGI_FORMAT_P010 )
            {
                quad->cropViewport[1] = quad->cropViewport[2] =
                quad->cropViewport[3] = quad->cropViewport[0];
                break;
            }
            /* fallthrough */
        case VLC_CODEC_I420_10L:
        case VLC_CODEC_I420:
            quad->cropViewport[1].TopLeftX = quad->cropViewport[0].TopLeftX / 2;
            quad->cropViewport[1].TopLeftY = quad->cropViewport[0].TopLeftY / 2;
            quad->cropViewport[1].Width    = quad->cropViewport[0].Width / 2;
            quad->cropViewport[1].Height   = quad->cropViewport[0].Height / 2;
            quad->cropViewport[2] = quad->cropViewport[1];
            break;
        }
        break;
    default:
        vlc_assert_unreachable();
    }
}