#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  server_string; int /*<<< orphan*/  address; int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_ifindex (TYPE_1__*) ; 
 int /*<<< orphan*/  in_addr_ifindex_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* strna (int /*<<< orphan*/ ) ; 

const char *dns_server_string(DnsServer *server) {
        assert(server);

        if (!server->server_string)
                (void) in_addr_ifindex_to_string(server->family, &server->address, dns_server_ifindex(server), &server->server_string);

        return strna(server->server_string);
}