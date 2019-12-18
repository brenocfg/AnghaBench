#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ element_size; int features; int /*<<< orphan*/  vtable_format_reference; } ;
struct TYPE_6__ {TYPE_1__ start; } ;
struct TYPE_7__ {TYPE_2__ x; } ;
typedef  TYPE_3__ sd_bus_vtable ;

/* Variables and functions */
 scalar_t__ VTABLE_ELEMENT_SIZE_242 ; 

__attribute__((used)) static int vtable_features(const sd_bus_vtable *vtable) {
        if (vtable[0].x.start.element_size < VTABLE_ELEMENT_SIZE_242 ||
            !vtable[0].x.start.vtable_format_reference)
                return 0;
        return vtable[0].x.start.features;
}