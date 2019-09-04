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
struct d3d_light {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IDirect3DLight ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  d3d_light_vtbl ; 
 struct d3d_light* impl_from_IDirect3DLight (TYPE_1__*) ; 

struct d3d_light *unsafe_impl_from_IDirect3DLight(IDirect3DLight *iface)
{
    if (!iface)
        return NULL;
    assert(iface->lpVtbl == &d3d_light_vtbl);

    return impl_from_IDirect3DLight(iface);
}