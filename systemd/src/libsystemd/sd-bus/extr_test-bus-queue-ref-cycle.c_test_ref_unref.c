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
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int log_tests_skipped (char*) ; 
 scalar_t__ sd_bus_message_new_method_call (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * sd_bus_message_unref (int /*<<< orphan*/ *) ; 
 int sd_bus_open_system (int /*<<< orphan*/ **) ; 
 scalar_t__ sd_bus_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sd_bus_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_ref_unref(void) {
        sd_bus_message *m = NULL;
        sd_bus *bus = NULL;
        int r;

        /* This test will result in a memory leak in <= v240, but not on v241. Hence to be really useful it
         * should be run through a leak tracker such as valgrind. */

        r = sd_bus_open_system(&bus);
        if (r < 0)
                return log_tests_skipped("Failed to connect to bus");

        /* Create a message and enqueue it (this shouldn't send it though as the connection setup is not complete yet) */
        assert_se(sd_bus_message_new_method_call(bus, &m, "foo.bar", "/foo", "quux.quux", "waldo") >= 0);
        assert_se(sd_bus_send(bus, m, NULL) >= 0);

        /* Let's now unref the message first and the bus second. */
        m = sd_bus_message_unref(m);
        bus = sd_bus_unref(bus);

        /* We should have a memory leak now on <= v240. Let's do this again, but destroy in the opposite
         * order. On v240 that too should be a leak. */

        r = sd_bus_open_system(&bus);
        if (r < 0)
                return log_tests_skipped("Failed to connect to bus");

        assert_se(sd_bus_message_new_method_call(bus, &m, "foo.bar", "/foo", "quux.quux", "waldo") >= 0);
        assert_se(sd_bus_send(bus, m, NULL) >= 0);

        /* Let's now unref things in the opposite order */
        bus = sd_bus_unref(bus);
        m = sd_bus_message_unref(m);

        return 0;
}