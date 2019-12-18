#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int bus_open_system_watch_bind_with_description (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bus_open_system_watch_bind(sd_bus **ret) {
        return bus_open_system_watch_bind_with_description(ret, NULL);
}