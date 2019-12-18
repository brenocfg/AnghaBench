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
struct TYPE_5__ {scalar_t__ n_inotify_watches; int /*<<< orphan*/  inotify_watches; int /*<<< orphan*/  inotify_fd; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_detach_inotify_event (TYPE_1__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 

void bus_close_inotify_fd(sd_bus *b) {
        assert(b);

        bus_detach_inotify_event(b);

        b->inotify_fd = safe_close(b->inotify_fd);
        b->inotify_watches = mfree(b->inotify_watches);
        b->n_inotify_watches = 0;
}