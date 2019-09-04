#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct d3drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirect3DRMDevice3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  d3drm_device3_vtbl ; 
 struct d3drm_device* impl_from_IDirect3DRMDevice3 (TYPE_1__*) ; 

struct d3drm_device *unsafe_impl_from_IDirect3DRMDevice3(IDirect3DRMDevice3 *iface)
{
    if (!iface)
        return NULL;
    assert(iface->lpVtbl == &d3drm_device3_vtbl);

    return impl_from_IDirect3DRMDevice3(iface);
}