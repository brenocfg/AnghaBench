#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* seat; int /*<<< orphan*/ * session_devices; } ;
struct TYPE_9__ {int /*<<< orphan*/  devices; } ;
typedef  int /*<<< orphan*/  SessionDevice ;
typedef  TYPE_1__ Seat ;
typedef  TYPE_2__ Device ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  seat_add_to_gc_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  seat_has_master_device (TYPE_1__*) ; 
 int /*<<< orphan*/  seat_send_changed (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_device_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_detach(Device *d) {
        Seat *s;
        SessionDevice *sd;

        assert(d);

        if (!d->seat)
                return;

        while ((sd = d->session_devices))
                session_device_free(sd);

        s = d->seat;
        LIST_REMOVE(devices, d->seat->devices, d);
        d->seat = NULL;

        if (!seat_has_master_device(s)) {
                seat_add_to_gc_queue(s);
                seat_send_changed(s, "CanGraphical", NULL);
        }
}