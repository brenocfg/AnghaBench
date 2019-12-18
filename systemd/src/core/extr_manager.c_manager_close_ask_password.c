#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  have_ask_password; int /*<<< orphan*/  ask_password_inotify_fd; int /*<<< orphan*/  ask_password_event_source; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_close_ask_password(Manager *m) {
        assert(m);

        m->ask_password_event_source = sd_event_source_unref(m->ask_password_event_source);
        m->ask_password_inotify_fd = safe_close(m->ask_password_inotify_fd);
        m->have_ask_password = -EINVAL;
}