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
struct TYPE_3__ {scalar_t__ code; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ sd_bus_error_map ;

/* Variables and functions */
 scalar_t__ BUS_ERROR_MAP_END_MARKER ; 

__attribute__((used)) static bool map_ok(const sd_bus_error_map *map) {
        for (; map->code != BUS_ERROR_MAP_END_MARKER; map++)
                if (!map->name || map->code <=0)
                        return false;
        return true;
}