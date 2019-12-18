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
typedef  int uint64_t ;
struct TYPE_6__ {scalar_t__ mdns_ipv6_scope; scalar_t__ mdns_ipv4_scope; scalar_t__ llmnr_ipv6_scope; scalar_t__ llmnr_ipv4_scope; scalar_t__ unicast_scope; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int SD_RESOLVED_DNS ; 
 int SD_RESOLVED_LLMNR_IPV4 ; 
 int SD_RESOLVED_LLMNR_IPV6 ; 
 int SD_RESOLVED_MDNS_IPV4 ; 
 int SD_RESOLVED_MDNS_IPV6 ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,int) ; 

__attribute__((used)) static int property_get_scopes_mask(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Link *l = userdata;
        uint64_t mask;

        assert(reply);
        assert(l);

        mask =  (l->unicast_scope ? SD_RESOLVED_DNS : 0) |
                (l->llmnr_ipv4_scope ? SD_RESOLVED_LLMNR_IPV4 : 0) |
                (l->llmnr_ipv6_scope ? SD_RESOLVED_LLMNR_IPV6 : 0) |
                (l->mdns_ipv4_scope ? SD_RESOLVED_MDNS_IPV4 : 0) |
                (l->mdns_ipv6_scope ? SD_RESOLVED_MDNS_IPV6 : 0);

        return sd_bus_message_append(reply, "t", mask);
}