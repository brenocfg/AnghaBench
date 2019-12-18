#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct d3d11_local_swapchain {int /*<<< orphan*/  swapchainTargetView; int /*<<< orphan*/  pixelFormat; int /*<<< orphan*/  d3d_dev; scalar_t__ dxgiswapChain4; int /*<<< orphan*/  dxgiswapChain; } ;
struct TYPE_12__ {int /*<<< orphan*/  MaxFrameAverageLightLevel; int /*<<< orphan*/  MaxContentLightLevel; int /*<<< orphan*/  MaxMasteringLuminance; int /*<<< orphan*/  MinMasteringLuminance; int /*<<< orphan*/ * WhitePoint; int /*<<< orphan*/ * RedPrimary; int /*<<< orphan*/ * BluePrimary; int /*<<< orphan*/ * GreenPrimary; } ;
typedef  TYPE_4__ libvlc_video_direct3d_hdr10_metadata_t ;
typedef  int /*<<< orphan*/  i_width ;
typedef  int /*<<< orphan*/  i_height ;
typedef  int /*<<< orphan*/  hdr10 ;
typedef  int UINT ;
struct TYPE_9__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_10__ {TYPE_1__ display; } ;
struct TYPE_11__ {TYPE_2__ vdcfg; } ;
struct TYPE_14__ {TYPE_3__ area; } ;
struct TYPE_13__ {int /*<<< orphan*/  MaxFrameAverageLightLevel; int /*<<< orphan*/  MaxContentLightLevel; int /*<<< orphan*/  MaxMasteringLuminance; int /*<<< orphan*/  MinMasteringLuminance; int /*<<< orphan*/ * WhitePoint; int /*<<< orphan*/ * RedPrimary; int /*<<< orphan*/ * BluePrimary; int /*<<< orphan*/ * GreenPrimary; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_5__ DXGI_HDR_METADATA_HDR10 ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ClearRenderTargets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DXGI_HDR_METADATA_TYPE_HDR10 ; 
 int /*<<< orphan*/  GUID_SWAPCHAIN_HEIGHT ; 
 int /*<<< orphan*/  GUID_SWAPCHAIN_WIDTH ; 
 int /*<<< orphan*/  IDXGISwapChain4_SetHDRMetaData (scalar_t__,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int /*<<< orphan*/  IDXGISwapChain_GetPrivateData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_6__* sys ; 
 int /*<<< orphan*/  vd ; 
 int /*<<< orphan*/  vout_display_SetSize (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

bool LocalSwapchainStartEndRendering( void *opaque, bool enter, const libvlc_video_direct3d_hdr10_metadata_t *p_hdr10 )
{
    struct d3d11_local_swapchain *display = opaque;

    if ( enter )
    {
#if VLC_WINSTORE_APP
        /* legacy UWP mode, the width/height was set in GUID_SWAPCHAIN_WIDTH/HEIGHT */
        uint32_t i_width;
        uint32_t i_height;
        UINT dataSize = sizeof(i_width);
        HRESULT hr = IDXGISwapChain_GetPrivateData(display->dxgiswapChain, &GUID_SWAPCHAIN_WIDTH, &dataSize, &i_width);
        if (SUCCEEDED(hr)) {
            dataSize = sizeof(i_height);
            hr = IDXGISwapChain_GetPrivateData(display->dxgiswapChain, &GUID_SWAPCHAIN_HEIGHT, &dataSize, &i_height);
            if (SUCCEEDED(hr)) {
                if (i_width != sys->area.vdcfg.display.width || i_height != sys->area.vdcfg.display.height)
                {
                    vout_display_SetSize(vd, i_width, i_height);
                }
            }
        }
#endif

        if ( display->dxgiswapChain4 && p_hdr10 != NULL )
        {
            DXGI_HDR_METADATA_HDR10 hdr10 = { 0 };
            hdr10.GreenPrimary[0] = p_hdr10->GreenPrimary[0];
            hdr10.GreenPrimary[1] = p_hdr10->GreenPrimary[1];
            hdr10.BluePrimary[0] = p_hdr10->BluePrimary[0];
            hdr10.BluePrimary[1] = p_hdr10->BluePrimary[1];
            hdr10.RedPrimary[0] = p_hdr10->RedPrimary[0];
            hdr10.RedPrimary[1] = p_hdr10->RedPrimary[1];
            hdr10.WhitePoint[0] = p_hdr10->WhitePoint[0];
            hdr10.WhitePoint[1] = p_hdr10->WhitePoint[1];
            hdr10.MinMasteringLuminance = p_hdr10->MinMasteringLuminance;
            hdr10.MaxMasteringLuminance = p_hdr10->MaxMasteringLuminance;
            hdr10.MaxContentLightLevel = p_hdr10->MaxContentLightLevel;
            hdr10.MaxFrameAverageLightLevel = p_hdr10->MaxFrameAverageLightLevel;
            IDXGISwapChain4_SetHDRMetaData( display->dxgiswapChain4, DXGI_HDR_METADATA_TYPE_HDR10, sizeof( hdr10 ), &hdr10 );
        }

        D3D11_ClearRenderTargets( &display->d3d_dev, display->pixelFormat, display->swapchainTargetView );
    }
    return true;
}