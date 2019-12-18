#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
struct TYPE_5__ {int /*<<< orphan*/  spike; TYPE_1__ reference; int /*<<< orphan*/  jitter; int /*<<< orphan*/  packet_count; int /*<<< orphan*/  dest; int /*<<< orphan*/  trans; int /*<<< orphan*/  recv; int /*<<< orphan*/  origin; int /*<<< orphan*/  root_dispersion; int /*<<< orphan*/  root_delay; int /*<<< orphan*/  precision; int /*<<< orphan*/  stratum; int /*<<< orphan*/  mode; int /*<<< orphan*/  version; int /*<<< orphan*/  leap; } ;
typedef  TYPE_2__ NTPStatusInfo ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,char*) ; 
 int sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read_array (int /*<<< orphan*/ *,char,void const**,size_t*) ; 

__attribute__((used)) static int map_ntp_message(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata) {
        NTPStatusInfo *p = userdata;
        const void *d;
        size_t sz;
        int32_t b;
        int r;

        assert(p);

        r = sd_bus_message_enter_container(m, 'r', "uuuuittayttttbtt");
        if (r < 0)
                return r;

        r = sd_bus_message_read(m, "uuuuitt",
                                &p->leap, &p->version, &p->mode, &p->stratum, &p->precision,
                                &p->root_delay, &p->root_dispersion);
        if (r < 0)
                return r;

        r = sd_bus_message_read_array(m, 'y', &d, &sz);
        if (r < 0)
                return r;

        r = sd_bus_message_read(m, "ttttbtt",
                                &p->origin, &p->recv, &p->trans, &p->dest,
                                &b, &p->packet_count, &p->jitter);
        if (r < 0)
                return r;

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return r;

        if (sz != 4)
                return -EINVAL;

        memcpy(p->reference.str, d, sz);

        p->spike = b;

        return 0;
}