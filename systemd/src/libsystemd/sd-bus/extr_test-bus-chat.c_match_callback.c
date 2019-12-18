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
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_message_get_member (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_callback(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        log_info("Match triggered! interface=%s member=%s", strna(sd_bus_message_get_interface(m)), strna(sd_bus_message_get_member(m)));
        return 0;
}