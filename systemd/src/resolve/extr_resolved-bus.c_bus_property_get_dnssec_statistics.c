#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {scalar_t__* n_dnssec_verdict; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 size_t DNSSEC_BOGUS ; 
 size_t DNSSEC_INDETERMINATE ; 
 size_t DNSSEC_INSECURE ; 
 size_t DNSSEC_SECURE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bus_property_get_dnssec_statistics(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;

        assert(reply);
        assert(m);

        return sd_bus_message_append(reply, "(tttt)",
                                     (uint64_t) m->n_dnssec_verdict[DNSSEC_SECURE],
                                     (uint64_t) m->n_dnssec_verdict[DNSSEC_INSECURE],
                                     (uint64_t) m->n_dnssec_verdict[DNSSEC_BOGUS],
                                     (uint64_t) m->n_dnssec_verdict[DNSSEC_INDETERMINATE]);
}