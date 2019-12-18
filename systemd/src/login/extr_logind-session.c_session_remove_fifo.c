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
struct TYPE_4__ {scalar_t__ fifo_path; int /*<<< orphan*/  fifo_fd; int /*<<< orphan*/  fifo_event_source; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ mfree (scalar_t__) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

__attribute__((used)) static void session_remove_fifo(Session *s) {
        assert(s);

        s->fifo_event_source = sd_event_source_unref(s->fifo_event_source);
        s->fifo_fd = safe_close(s->fifo_fd);

        if (s->fifo_path) {
                (void) unlink(s->fifo_path);
                s->fifo_path = mfree(s->fifo_path);
        }
}