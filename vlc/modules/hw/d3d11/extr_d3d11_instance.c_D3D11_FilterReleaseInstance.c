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
struct TYPE_5__ {int /*<<< orphan*/ * d3dcontext; } ;
typedef  TYPE_1__ d3d11_device_t ;
struct TYPE_6__ {int /*<<< orphan*/ * d3dcontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ReleaseDevice (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ device ; 
 int /*<<< orphan*/  inst_lock ; 
 scalar_t__ instances ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void D3D11_FilterReleaseInstance(d3d11_device_t *d3d_dev)
{
    vlc_mutex_lock(&inst_lock);
    if (d3d_dev->d3dcontext && d3d_dev->d3dcontext == device.d3dcontext)
    {
        assert(instances != 0);
        if (--instances == 0)
            device.d3dcontext = NULL;
    }
    D3D11_ReleaseDevice(d3d_dev);
    vlc_mutex_unlock(&inst_lock);
}