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
struct ddraw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3d_light {int ref; struct ddraw* ddraw; TYPE_1__ IDirect3DLight_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d_light_vtbl ; 

void d3d_light_init(struct d3d_light *light, struct ddraw *ddraw)
{
    light->IDirect3DLight_iface.lpVtbl = &d3d_light_vtbl;
    light->ref = 1;
    light->ddraw = ddraw;
}