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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_socket_setup (int /*<<< orphan*/ *) ; 
 int bus_socket_start_auth (int /*<<< orphan*/ *) ; 

int bus_socket_take_fd(sd_bus *b) {
        assert(b);

        bus_socket_setup(b);

        return bus_socket_start_auth(b);
}