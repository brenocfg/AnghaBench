#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_6__ {scalar_t__ tx_bytes; scalar_t__ rx_bytes; } ;
struct TYPE_5__ {scalar_t__ tx_bytes; scalar_t__ rx_bytes; } ;
struct TYPE_8__ {TYPE_2__ stats_new; TYPE_1__ stats_old; int /*<<< orphan*/  stats_updated; TYPE_3__* manager; } ;
struct TYPE_7__ {scalar_t__ speed_meter_usec_old; scalar_t__ speed_meter_usec_new; int /*<<< orphan*/  use_speed_meter; } ;
typedef  TYPE_3__ Manager ;
typedef  TYPE_4__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_SPEED_METER_INACTIVE ; 
 double UINT64_MAX ; 
 double USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int sd_bus_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int property_get_bit_rates(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Link *link = userdata;
        Manager *manager;
        double interval_sec;
        uint64_t tx, rx;

        assert(bus);
        assert(reply);
        assert(userdata);

        manager = link->manager;

        if (!manager->use_speed_meter)
                return sd_bus_error_set(error, BUS_ERROR_SPEED_METER_INACTIVE, "Speed meter is disabled.");

        if (manager->speed_meter_usec_old == 0)
                return sd_bus_error_set(error, BUS_ERROR_SPEED_METER_INACTIVE, "Speed meter is not active.");

        if (!link->stats_updated)
                return sd_bus_error_set(error, BUS_ERROR_SPEED_METER_INACTIVE, "Failed to measure bit-rates.");

        assert(manager->speed_meter_usec_new > manager->speed_meter_usec_old);
        interval_sec = (manager->speed_meter_usec_new - manager->speed_meter_usec_old) / USEC_PER_SEC;

        if (link->stats_new.tx_bytes > link->stats_old.tx_bytes)
                tx = (uint64_t) ((link->stats_new.tx_bytes - link->stats_old.tx_bytes) / interval_sec);
        else
                tx = (uint64_t) ((UINT64_MAX - (link->stats_old.tx_bytes - link->stats_new.tx_bytes)) / interval_sec);

        if (link->stats_new.rx_bytes > link->stats_old.rx_bytes)
                rx = (uint64_t) ((link->stats_new.rx_bytes - link->stats_old.rx_bytes) / interval_sec);
        else
                rx = (uint64_t) ((UINT64_MAX - (link->stats_old.rx_bytes - link->stats_new.rx_bytes)) / interval_sec);

        return sd_bus_message_append(reply, "(tt)", tx, rx);
}