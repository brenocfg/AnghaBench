#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct d3d11_local_swapchain {int /*<<< orphan*/  d3d_dev; int /*<<< orphan*/ * dxgiswapChain; int /*<<< orphan*/ * dxgiswapChain4; int /*<<< orphan*/ ** swapchainTargetView; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  D3D11_ReleaseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11RenderTargetView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGISwapChain4_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDXGISwapChain_Release (int /*<<< orphan*/ *) ; 

void LocalSwapchainCleanupDevice( void *opaque )
{
    struct d3d11_local_swapchain *display = opaque;
    for (size_t i=0; i < ARRAY_SIZE(display->swapchainTargetView); i++)
    {
        if (display->swapchainTargetView[i]) {
            ID3D11RenderTargetView_Release(display->swapchainTargetView[i]);
            display->swapchainTargetView[i] = NULL;
        }
    }
    if (display->dxgiswapChain4)
    {
        IDXGISwapChain4_Release(display->dxgiswapChain4);
        display->dxgiswapChain4 = NULL;
    }
    if (display->dxgiswapChain)
    {
        IDXGISwapChain_Release(display->dxgiswapChain);
        display->dxgiswapChain = NULL;
    }

    D3D11_ReleaseDevice( &display->d3d_dev );
}