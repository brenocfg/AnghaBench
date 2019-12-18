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
 scalar_t__ sd_bus_emit_object_removed (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int emit_object_removed(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        int r;

        assert_se(sd_bus_emit_object_removed(sd_bus_message_get_bus(m), "/value/a/x") >= 0);

        r = sd_bus_reply_method_return(m, NULL);
        assert_se(r >= 0);

        return 1;
}