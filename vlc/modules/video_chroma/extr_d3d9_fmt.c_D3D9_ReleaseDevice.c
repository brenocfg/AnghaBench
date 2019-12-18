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
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ d3d9_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9_Release (int /*<<< orphan*/ *) ; 

void D3D9_ReleaseDevice(d3d9_device_t *d3d_dev)
{
    if (d3d_dev->dev)
    {
       IDirect3DDevice9_Release(d3d_dev->dev);
       d3d_dev->dev = NULL;
    }
}