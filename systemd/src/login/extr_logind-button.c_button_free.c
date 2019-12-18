#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fd; struct TYPE_8__* seat; struct TYPE_8__* name; int /*<<< orphan*/  check_event_source; int /*<<< orphan*/  io_event_source; TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  buttons; } ;
typedef  TYPE_2__ Button ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

void button_free(Button *b) {
        assert(b);

        hashmap_remove(b->manager->buttons, b->name);

        sd_event_source_unref(b->io_event_source);
        sd_event_source_unref(b->check_event_source);

        if (b->fd >= 0)
                /* If the device has been unplugged close() returns
                 * ENODEV, let's ignore this, hence we don't use
                 * safe_close() */
                (void) close(b->fd);

        free(b->name);
        free(b->seat);
        free(b);
}