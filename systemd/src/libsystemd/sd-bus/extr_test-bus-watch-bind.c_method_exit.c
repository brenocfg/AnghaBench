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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  sd_bus_get_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_exit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int method_exit(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        log_info("Got Exit() call");
        assert_se(sd_event_exit(sd_bus_get_event(sd_bus_message_get_bus(m)), 1) >= 0);
        return sd_bus_reply_method_return(m, NULL);
}