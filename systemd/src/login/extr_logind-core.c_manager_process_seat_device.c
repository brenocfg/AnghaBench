#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_11__ {int /*<<< orphan*/  seat; } ;
struct TYPE_10__ {int /*<<< orphan*/  seats; int /*<<< orphan*/  devices; } ;
typedef  int /*<<< orphan*/  Seat ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Device ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ACTION_REMOVE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  device_attach (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_for_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_free (TYPE_2__*) ; 
 void* hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_device_warning (int /*<<< orphan*/ *,char*,char const*) ; 
 int manager_add_device (TYPE_1__*,char const*,int,TYPE_2__**) ; 
 int manager_add_seat (TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int sd_device_get_syspath (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_has_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  seat_add_to_gc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_name_is_valid (char const*) ; 
 int /*<<< orphan*/  seat_start (int /*<<< orphan*/ *) ; 

int manager_process_seat_device(Manager *m, sd_device *d) {
        Device *device;
        int r;

        assert(m);

        if (device_for_action(d, DEVICE_ACTION_REMOVE)) {
                const char *syspath;

                r = sd_device_get_syspath(d, &syspath);
                if (r < 0)
                        return 0;

                device = hashmap_get(m->devices, syspath);
                if (!device)
                        return 0;

                seat_add_to_gc_queue(device->seat);
                device_free(device);

        } else {
                const char *sn, *syspath;
                bool master;
                Seat *seat;

                if (sd_device_get_property_value(d, "ID_SEAT", &sn) < 0 || isempty(sn))
                        sn = "seat0";

                if (!seat_name_is_valid(sn)) {
                        log_device_warning(d, "Device with invalid seat name %s found, ignoring.", sn);
                        return 0;
                }

                seat = hashmap_get(m->seats, sn);
                master = sd_device_has_tag(d, "master-of-seat") > 0;

                /* Ignore non-master devices for unknown seats */
                if (!master && !seat)
                        return 0;

                r = sd_device_get_syspath(d, &syspath);
                if (r < 0)
                        return r;

                r = manager_add_device(m, syspath, master, &device);
                if (r < 0)
                        return r;

                if (!seat) {
                        r = manager_add_seat(m, sn, &seat);
                        if (r < 0) {
                                if (!device->seat)
                                        device_free(device);

                                return r;
                        }
                }

                device_attach(device, seat);
                seat_start(seat);
        }

        return 0;
}