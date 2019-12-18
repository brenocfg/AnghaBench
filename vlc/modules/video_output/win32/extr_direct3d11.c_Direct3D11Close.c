#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_7__ {scalar_t__ swapCb; int /*<<< orphan*/  outside_opaque; int /*<<< orphan*/  d3d_dev; } ;
typedef  TYPE_2__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ReleaseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Direct3D11DestroyResources (TYPE_1__*) ; 
 int /*<<< orphan*/  LocalSwapchainCleanupDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ LocalSwapchainSwap ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 

__attribute__((used)) static void Direct3D11Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    Direct3D11DestroyResources(vd);

    D3D11_ReleaseDevice( &sys->d3d_dev );

    if ( sys->swapCb == LocalSwapchainSwap )
        LocalSwapchainCleanupDevice( sys->outside_opaque );

    msg_Dbg(vd, "Direct3D11 display adapter closed");
}