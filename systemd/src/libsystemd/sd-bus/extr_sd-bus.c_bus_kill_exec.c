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
struct TYPE_3__ {scalar_t__ busexec_pid; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 scalar_t__ pid_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  sigterm_wait (scalar_t__) ; 

__attribute__((used)) static void bus_kill_exec(sd_bus *bus) {
        if (pid_is_valid(bus->busexec_pid) > 0) {
                sigterm_wait(bus->busexec_pid);
                bus->busexec_pid = 0;
        }
}