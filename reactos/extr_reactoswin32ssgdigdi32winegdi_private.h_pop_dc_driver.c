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
struct gdi_dc_funcs {int dummy; } ;
struct TYPE_6__ {TYPE_1__* physDev; } ;
struct TYPE_5__ {struct TYPE_5__* next; struct gdi_dc_funcs const* funcs; } ;
typedef  TYPE_1__* PHYSDEV ;
typedef  TYPE_2__ DC ;

/* Variables and functions */

__attribute__((used)) static inline PHYSDEV pop_dc_driver( DC *dc, const struct gdi_dc_funcs *funcs )
{
    PHYSDEV dev, *pdev = &dc->physDev;
    while (*pdev && (*pdev)->funcs != funcs) pdev = &(*pdev)->next;
    if (!*pdev) return NULL;
    dev = *pdev;
    *pdev = dev->next;
    return dev;
}