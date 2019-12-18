#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3d11_local_swapchain {int /*<<< orphan*/  obj; int /*<<< orphan*/  dxgiswapChain; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DXGI_PRESENT_PARAMETERS ;

/* Variables and functions */
 scalar_t__ DXGI_ERROR_DEVICE_REMOVED ; 
 scalar_t__ DXGI_ERROR_DEVICE_RESET ; 
 scalar_t__ IDXGISwapChain1_Present1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void LocalSwapchainSwap( void *opaque )
{
    struct d3d11_local_swapchain *display = opaque;
    DXGI_PRESENT_PARAMETERS presentParams = { 0 };

    HRESULT hr = IDXGISwapChain1_Present1( display->dxgiswapChain, 0, 0, &presentParams );
    if ( hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET )
    {
        /* TODO device lost */
        msg_Err( display->obj, "SwapChain Present failed. (hr=0x%lX)", hr );
    }
}