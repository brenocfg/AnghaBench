#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  d3dcontext; } ;
struct d3d11_local_swapchain {int /*<<< orphan*/ * swapchainTargetView; TYPE_1__ d3d_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11DeviceContext_OMSetRenderTargets (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool LocalSwapchainSelectPlane( void *opaque, size_t plane )
{
    struct d3d11_local_swapchain *display = opaque;
    if (!display->swapchainTargetView[plane])
        return false;
    ID3D11DeviceContext_OMSetRenderTargets(display->d3d_dev.d3dcontext, 1,
                                            &display->swapchainTargetView[plane], NULL);
    return true;
}