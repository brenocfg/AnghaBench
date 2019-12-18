#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int formatTexture; } ;
typedef  TYPE_1__ d3d_format_t ;
struct TYPE_6__ {int /*<<< orphan*/  d3dcontext; } ;
typedef  TYPE_2__ d3d11_device_t ;
typedef  int /*<<< orphan*/  ID3D11RenderTargetView ;
typedef  float FLOAT ;

/* Variables and functions */
 int D3D11_MAX_RENDER_TARGET ; 
#define  DXGI_FORMAT_AYUV 136 
#define  DXGI_FORMAT_B5G6R5_UNORM 135 
#define  DXGI_FORMAT_B8G8R8A8_UNORM 134 
#define  DXGI_FORMAT_B8G8R8X8_UNORM 133 
#define  DXGI_FORMAT_NV12 132 
#define  DXGI_FORMAT_P010 131 
#define  DXGI_FORMAT_R10G10B10A2_UNORM 130 
#define  DXGI_FORMAT_R8G8B8A8_UNORM 129 
#define  DXGI_FORMAT_YUY2 128 
 int /*<<< orphan*/  ID3D11DeviceContext_ClearRenderTargetView (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float const*) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

void D3D11_ClearRenderTargets(d3d11_device_t *d3d_dev, const d3d_format_t *cfg,
                              ID3D11RenderTargetView *targets[D3D11_MAX_RENDER_TARGET])
{
    static const FLOAT blackY[1] = {0.0f};
    static const FLOAT blackUV[2] = {0.5f, 0.5f};
    static const FLOAT blackRGBA[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    static const FLOAT blackYUY2[4] = {0.0f, 0.5f, 0.0f, 0.5f};
    static const FLOAT blackVUYA[4] = {0.5f, 0.5f, 0.0f, 1.0f};

    static_assert(D3D11_MAX_RENDER_TARGET >= 2, "we need at least 2 RenderTargetView for NV12/P010");

    switch (cfg->formatTexture)
    {
    case DXGI_FORMAT_NV12:
    case DXGI_FORMAT_P010:
        ID3D11DeviceContext_ClearRenderTargetView( d3d_dev->d3dcontext, targets[0], blackY);
        ID3D11DeviceContext_ClearRenderTargetView( d3d_dev->d3dcontext, targets[1], blackUV);
        break;
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM:
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_B5G6R5_UNORM:
        ID3D11DeviceContext_ClearRenderTargetView( d3d_dev->d3dcontext, targets[0], blackRGBA);
        break;
    case DXGI_FORMAT_YUY2:
        ID3D11DeviceContext_ClearRenderTargetView( d3d_dev->d3dcontext, targets[0], blackYUY2);
        break;
    case DXGI_FORMAT_AYUV:
        ID3D11DeviceContext_ClearRenderTargetView( d3d_dev->d3dcontext, targets[0], blackVUYA);
        break;
    default:
        vlc_assert_unreachable();
    }
}