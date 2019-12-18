#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_2__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
#define  BUS_NAME_ALREADY_OWNER 131 
#define  BUS_NAME_EXISTS 130 
#define  BUS_NAME_IN_QUEUE 129 
#define  BUS_NAME_PRIMARY_OWNER 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_enter_closing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_debug_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_message_get_errno (int /*<<< orphan*/ *) ; 
 TYPE_1__* sd_bus_message_get_error (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_message_is_method_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static int default_request_name_handler(
                sd_bus_message *m,
                void *userdata,
                sd_bus_error *ret_error) {

        uint32_t ret;
        int r;

        assert(m);

        if (sd_bus_message_is_method_error(m, NULL)) {
                log_debug_errno(sd_bus_message_get_errno(m),
                                "Unable to request name, failing connection: %s",
                                sd_bus_message_get_error(m)->message);

                bus_enter_closing(sd_bus_message_get_bus(m));
                return 1;
        }

        r = sd_bus_message_read(m, "u", &ret);
        if (r < 0)
                return r;

        switch (ret) {

        case BUS_NAME_ALREADY_OWNER:
                log_debug("Already owner of requested service name, ignoring.");
                return 1;

        case BUS_NAME_IN_QUEUE:
                log_debug("In queue for requested service name.");
                return 1;

        case BUS_NAME_PRIMARY_OWNER:
                log_debug("Successfully acquired requested service name.");
                return 1;

        case BUS_NAME_EXISTS:
                log_debug("Requested service name already owned, failing connection.");
                bus_enter_closing(sd_bus_message_get_bus(m));
                return 1;
        }

        log_debug("Unexpected response from RequestName(), failing connection.");
        bus_enter_closing(sd_bus_message_get_bus(m));
        return 1;
}