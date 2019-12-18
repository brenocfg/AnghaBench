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
typedef  int /*<<< orphan*/  uint64_t ;
struct context {int quit; int /*<<< orphan*/ * fds; } ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 void* INT_TO_PTR (int) ; 
 int /*<<< orphan*/  UINT_TO_PTR (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  enumerator2_callback ; 
 int /*<<< orphan*/  enumerator_callback ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 scalar_t__ sd_bus_add_fallback_vtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_bus_add_node_enumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_add_object_manager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sd_bus_add_object_vtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,struct context*) ; 
 int /*<<< orphan*/  sd_bus_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_new (int /*<<< orphan*/ **) ; 
 int sd_bus_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_bus_set_server (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_bus_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_unref (int /*<<< orphan*/ *) ; 
 int sd_bus_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_id128_randomize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtable ; 
 int /*<<< orphan*/  vtable2 ; 

__attribute__((used)) static void *server(void *p) {
        struct context *c = p;
        sd_bus *bus = NULL;
        sd_id128_t id;
        int r;

        c->quit = false;

        assert_se(sd_id128_randomize(&id) >= 0);

        assert_se(sd_bus_new(&bus) >= 0);
        assert_se(sd_bus_set_fd(bus, c->fds[0], c->fds[0]) >= 0);
        assert_se(sd_bus_set_server(bus, 1, id) >= 0);

        assert_se(sd_bus_add_object_vtable(bus, NULL, "/foo", "org.freedesktop.systemd.test", vtable, c) >= 0);
        assert_se(sd_bus_add_object_vtable(bus, NULL, "/foo", "org.freedesktop.systemd.test2", vtable, c) >= 0);
        assert_se(sd_bus_add_fallback_vtable(bus, NULL, "/value", "org.freedesktop.systemd.ValueTest", vtable2, NULL, UINT_TO_PTR(20)) >= 0);
        assert_se(sd_bus_add_node_enumerator(bus, NULL, "/value", enumerator_callback, NULL) >= 0);
        assert_se(sd_bus_add_node_enumerator(bus, NULL, "/value/a", enumerator2_callback, NULL) >= 0);
        assert_se(sd_bus_add_object_manager(bus, NULL, "/value") >= 0);
        assert_se(sd_bus_add_object_manager(bus, NULL, "/value/a") >= 0);

        assert_se(sd_bus_start(bus) >= 0);

        log_error("Entering event loop on server");

        while (!c->quit) {
                log_error("Loop!");

                r = sd_bus_process(bus, NULL);
                if (r < 0) {
                        log_error_errno(r, "Failed to process requests: %m");
                        goto fail;
                }

                if (r == 0) {
                        r = sd_bus_wait(bus, (uint64_t) -1);
                        if (r < 0) {
                                log_error_errno(r, "Failed to wait: %m");
                                goto fail;
                        }

                        continue;
                }
        }

        r = 0;

fail:
        if (bus) {
                sd_bus_flush(bus);
                sd_bus_unref(bus);
        }

        return INT_TO_PTR(r);
}