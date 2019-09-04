#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gdi_dc_funcs {scalar_t__ priority; } ;
struct TYPE_7__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdc; struct TYPE_6__* next; struct gdi_dc_funcs const* funcs; } ;
typedef  TYPE_1__* PHYSDEV ;

/* Variables and functions */
 TYPE_4__* CONTAINING_RECORD (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINEDC ; 
 int /*<<< orphan*/  physDev ; 

void
push_dc_driver_ros(
    PHYSDEV *dev,
    PHYSDEV physdev,
    const struct gdi_dc_funcs *funcs)
{
    while ((*dev)->funcs->priority > funcs->priority) dev = &(*dev)->next;
    physdev->funcs = funcs;
    physdev->next = *dev;
    physdev->hdc = CONTAINING_RECORD(dev, WINEDC, physDev)->hdc;
    *dev = physdev;
}