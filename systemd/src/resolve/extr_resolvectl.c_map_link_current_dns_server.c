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
typedef  void sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void*) ; 
 int read_dns_server_one (void*,int,void*) ; 

__attribute__((used)) static int map_link_current_dns_server(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata) {
        assert(m);
        assert(userdata);

        return read_dns_server_one(m, false, userdata);
}