#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ sd_bus_error ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warning_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_error_get_errno (TYPE_1__ const*) ; 
 TYPE_1__* sd_bus_message_get_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_hostname_handler(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        Manager *manager = userdata;
        const sd_bus_error *e;

        assert(m);
        assert(manager);

        e = sd_bus_message_get_error(m);
        if (e)
                log_warning_errno(sd_bus_error_get_errno(e), "Could not set hostname: %s", e->message);

        return 1;
}