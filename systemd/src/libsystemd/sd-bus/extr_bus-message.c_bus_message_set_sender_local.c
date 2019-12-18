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
struct TYPE_7__ {char* unique_name; int well_known_names_local; int mask; } ;
struct TYPE_8__ {char* sender; int creds_mask; TYPE_1__ creds; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  TYPE_2__ sd_bus ;

/* Variables and functions */
 int SD_BUS_CREDS_UNIQUE_NAME ; 
 int SD_BUS_CREDS_WELL_KNOWN_NAMES ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

void bus_message_set_sender_local(sd_bus *bus, sd_bus_message *m) {
        assert(bus);
        assert(m);

        m->sender = m->creds.unique_name = (char*) "org.freedesktop.DBus.Local";
        m->creds.well_known_names_local = true;
        m->creds.mask |= (SD_BUS_CREDS_UNIQUE_NAME|SD_BUS_CREDS_WELL_KNOWN_NAMES) & bus->creds_mask;
}