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
struct d3d_viewport {int ref; int use_vp2; int /*<<< orphan*/  light_list; struct ddraw* ddraw; TYPE_1__ IDirect3DViewport3_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d_viewport_vtbl ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

void d3d_viewport_init(struct d3d_viewport *viewport, struct ddraw *ddraw)
{
    viewport->IDirect3DViewport3_iface.lpVtbl = &d3d_viewport_vtbl;
    viewport->ref = 1;
    viewport->ddraw = ddraw;
    viewport->use_vp2 = 0xff;
    list_init(&viewport->light_list);
}