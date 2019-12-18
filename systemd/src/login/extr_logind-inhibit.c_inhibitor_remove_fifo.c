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
struct TYPE_4__ {scalar_t__ fifo_path; int /*<<< orphan*/  fifo_fd; int /*<<< orphan*/  event_source; } ;
typedef  TYPE_1__ Inhibitor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ mfree (scalar_t__) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

__attribute__((used)) static void inhibitor_remove_fifo(Inhibitor *i) {
        assert(i);

        i->event_source = sd_event_source_unref(i->event_source);
        i->fifo_fd = safe_close(i->fifo_fd);

        if (i->fifo_path) {
                (void) unlink(i->fifo_path);
                i->fifo_path = mfree(i->fifo_path);
        }
}