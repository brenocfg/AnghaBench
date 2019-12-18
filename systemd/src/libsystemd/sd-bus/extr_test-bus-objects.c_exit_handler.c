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
struct context {int quit; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int exit_handler(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        struct context *c = userdata;
        int r;

        c->quit = true;

        log_info("Exit called");

        r = sd_bus_reply_method_return(m, "");
        assert_se(r >= 0);

        return 1;
}