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
typedef  int /*<<< orphan*/  WINEDC ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * funcs; } ;
typedef  TYPE_1__* PHYSDEV ;

/* Variables and functions */
 int /*<<< orphan*/  DummyPhysDevFuncs ; 
 int /*<<< orphan*/ * get_nulldrv_dc (TYPE_1__*) ; 

WINEDC* get_physdev_dc( PHYSDEV dev )
{
    while (dev->funcs != &DummyPhysDevFuncs)
        dev = dev->next;
    return get_nulldrv_dc( dev );
}