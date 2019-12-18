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
struct inotify_event {int mask; } ;
struct inotify_context {int delete_self_handler_called; } ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 int IN_DELETE_SELF ; 
 int IN_IGNORED ; 
 int IN_Q_OVERFLOW ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  maybe_exit (int /*<<< orphan*/ *,struct inotify_context*) ; 

__attribute__((used)) static int delete_self_handler(sd_event_source *s, const struct inotify_event *ev, void *userdata) {
        struct inotify_context *c = userdata;

        if (ev->mask & IN_Q_OVERFLOW) {
                log_info("delete-self-handler: overflow");
                c->delete_self_handler_called = true;
        } else if (ev->mask & IN_DELETE_SELF) {
                log_info("delete-self-handler: delete-self");
                c->delete_self_handler_called = true;
        } else if (ev->mask & IN_IGNORED) {
                log_info("delete-self-handler: ignore");
        } else
                assert_not_reached("unexpected inotify event (delete-self)");

        maybe_exit(s, c);
        return 1;
}