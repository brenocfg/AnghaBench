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
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ sd_bus_emit_properties_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int notify_test(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        int r;

        assert_se(sd_bus_emit_properties_changed(sd_bus_message_get_bus(m), m->path, "org.freedesktop.systemd.ValueTest", "Value", NULL) >= 0);

        r = sd_bus_reply_method_return(m, NULL);
        assert_se(r >= 0);

        return 1;
}