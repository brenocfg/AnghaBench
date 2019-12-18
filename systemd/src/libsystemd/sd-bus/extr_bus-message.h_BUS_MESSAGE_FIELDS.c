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
typedef  void uint8_t ;
struct bus_header {int dummy; } ;
struct TYPE_3__ {scalar_t__ header; } ;
typedef  TYPE_1__ sd_bus_message ;

/* Variables and functions */

__attribute__((used)) static inline void* BUS_MESSAGE_FIELDS(sd_bus_message *m) {
        return (uint8_t*) m->header + sizeof(struct bus_header);
}