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
struct TYPE_5__ {scalar_t__ d3ddevice; } ;
struct d3d11_local_swapchain {int /*<<< orphan*/  obj; int /*<<< orphan*/  dxgiswapChain; int /*<<< orphan*/ * swapchainHwnd; TYPE_1__ d3d_dev; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {scalar_t__ Format; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDXGIFactory2 ;
typedef  int /*<<< orphan*/  IDXGIAdapter ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ DXGI_SWAP_CHAIN_DESC1 ;

/* Variables and functions */
 int /*<<< orphan*/ * D3D11DeviceAdapter (scalar_t__) ; 
 scalar_t__ DXGI_ERROR_INVALID_CALL ; 
 scalar_t__ DXGI_FORMAT_R10G10B10A2_UNORM ; 
 scalar_t__ DXGI_FORMAT_R8G8B8A8_UNORM ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FillSwapChainDesc (struct d3d11_local_swapchain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IDXGIAdapter_GetParent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDXGIAdapter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDXGIFactory2_CreateSwapChainForHwnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGIFactory2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDXGIFactory2 ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CreateSwapchain(struct d3d11_local_swapchain *display, UINT width, UINT height)
{
    if (display->swapchainHwnd == NULL)
    {
        msg_Err(display->obj, "missing a HWND to create the swapchain");
        return;
    }

    DXGI_SWAP_CHAIN_DESC1 scd;
    FillSwapChainDesc(display, width, height, &scd);

    IDXGIAdapter *dxgiadapter = D3D11DeviceAdapter(display->d3d_dev.d3ddevice);
    if (unlikely(dxgiadapter==NULL)) {
        msg_Err(display->obj, "Could not get the DXGI Adapter");
        return;
    }

    IDXGIFactory2 *dxgifactory;
    HRESULT hr = IDXGIAdapter_GetParent(dxgiadapter, &IID_IDXGIFactory2, (void **)&dxgifactory);
    IDXGIAdapter_Release(dxgiadapter);
    if (FAILED(hr)) {
        msg_Err(display->obj, "Could not get the DXGI Factory. (hr=0x%lX)", hr);
        return;
    }

    hr = IDXGIFactory2_CreateSwapChainForHwnd(dxgifactory, (IUnknown *)display->d3d_dev.d3ddevice,
                                              display->swapchainHwnd, &scd,
                                              NULL, NULL, &display->dxgiswapChain);
    if (hr == DXGI_ERROR_INVALID_CALL && scd.Format == DXGI_FORMAT_R10G10B10A2_UNORM)
    {
        msg_Warn(display->obj, "10 bits swapchain failed, try 8 bits");
        scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        hr = IDXGIFactory2_CreateSwapChainForHwnd(dxgifactory, (IUnknown *)display->d3d_dev.d3ddevice,
                                                  display->swapchainHwnd, &scd,
                                                  NULL, NULL, &display->dxgiswapChain);
    }
    IDXGIFactory2_Release(dxgifactory);
    if (FAILED(hr)) {
        msg_Err(display->obj, "Could not create the SwapChain. (hr=0x%lX)", hr);
    }
}