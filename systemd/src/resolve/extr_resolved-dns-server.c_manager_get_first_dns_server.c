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
struct TYPE_4__ {int /*<<< orphan*/ * fallback_dns_servers; int /*<<< orphan*/ * dns_servers; } ;
typedef  TYPE_1__ Manager ;
typedef  int DnsServerType ;
typedef  int /*<<< orphan*/  DnsServer ;

/* Variables and functions */
#define  DNS_SERVER_FALLBACK 129 
#define  DNS_SERVER_SYSTEM 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

DnsServer *manager_get_first_dns_server(Manager *m, DnsServerType t) {
        assert(m);

        switch (t) {

        case DNS_SERVER_SYSTEM:
                return m->dns_servers;

        case DNS_SERVER_FALLBACK:
                return m->fallback_dns_servers;

        default:
                return NULL;
        }
}