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
struct bus_header {int dummy; } ;
struct TYPE_3__ {size_t body_size; int /*<<< orphan*/  fields_size; } ;
typedef  TYPE_1__ sd_bus_message ;

/* Variables and functions */
 size_t ALIGN8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t BUS_MESSAGE_SIZE(sd_bus_message *m) {
        return
                sizeof(struct bus_header) +
                ALIGN8(m->fields_size) +
                m->body_size;
}