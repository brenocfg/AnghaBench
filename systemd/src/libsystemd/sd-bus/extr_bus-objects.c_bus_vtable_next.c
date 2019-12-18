#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int element_size; } ;
struct TYPE_8__ {TYPE_1__ start; } ;
struct TYPE_9__ {TYPE_2__ x; } ;
typedef  TYPE_3__ sd_bus_vtable ;

/* Variables and functions */

const sd_bus_vtable* bus_vtable_next(const sd_bus_vtable *vtable, const sd_bus_vtable *v) {
        return (const sd_bus_vtable*) ((char*) v + vtable[0].x.start.element_size);
}