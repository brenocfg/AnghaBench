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
struct inotify_event {int mask; char const* name; } ;
struct inotify_context {unsigned int create_overflow; unsigned int n_create_events; unsigned int* create_called; } ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 int IN_CREATE ; 
 int IN_DELETE ; 
 int IN_Q_OVERFLOW ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_debug (char*,char const*,char const*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,...) ; 
 int /*<<< orphan*/  maybe_exit (int /*<<< orphan*/ *,struct inotify_context*) ; 
 scalar_t__ safe_atou (char const*,unsigned int*) ; 
 scalar_t__ sd_event_source_get_description (int /*<<< orphan*/ *,char const**) ; 
 int streq (char const*,char*) ; 

__attribute__((used)) static int inotify_handler(sd_event_source *s, const struct inotify_event *ev, void *userdata) {
        struct inotify_context *c = userdata;
        const char *description;
        unsigned bit, n;

        assert_se(sd_event_source_get_description(s, &description) >= 0);
        assert_se(safe_atou(description, &n) >= 0);

        assert_se(n <= 3);
        bit = 1U << n;

        if (ev->mask & IN_Q_OVERFLOW) {
                log_info("inotify-handler <%s>: overflow", description);
                c->create_overflow |= bit;
        } else if (ev->mask & IN_CREATE) {
                unsigned i;

                log_debug("inotify-handler <%s>: create on %s", description, ev->name);

                if (!streq(ev->name, "sub")) {
                        assert_se(safe_atou(ev->name, &i) >= 0);

                        assert_se(i < c->n_create_events);
                        c->create_called[i] |= bit;
                }
        } else if (ev->mask & IN_DELETE) {
                log_info("inotify-handler <%s>: delete of %s", description, ev->name);
                assert_se(streq(ev->name, "sub"));
        } else
                assert_not_reached("unexpected inotify event");

        maybe_exit(s, c);
        return 1;
}