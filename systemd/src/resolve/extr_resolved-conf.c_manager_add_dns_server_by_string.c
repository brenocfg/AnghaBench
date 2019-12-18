#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union in_addr_union {int dummy; } in_addr_union ;
typedef  char const Manager ;
typedef  int /*<<< orphan*/  DnsServerType ;
typedef  int /*<<< orphan*/  DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  dns_server_address_valid (int,union in_addr_union*) ; 
 int /*<<< orphan*/ * dns_server_find (int /*<<< orphan*/ ,int,union in_addr_union*,int) ; 
 int /*<<< orphan*/  dns_server_move_back_and_unmark (int /*<<< orphan*/ *) ; 
 int dns_server_new (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,union in_addr_union*,int) ; 
 int in_addr_ifindex_from_string_auto (char const*,int*,union in_addr_union*,int*) ; 
 int /*<<< orphan*/  manager_get_first_dns_server (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int manager_add_dns_server_by_string(Manager *m, DnsServerType type, const char *word) {
        union in_addr_union address;
        int family, r, ifindex = 0;
        DnsServer *s;

        assert(m);
        assert(word);

        r = in_addr_ifindex_from_string_auto(word, &family, &address, &ifindex);
        if (r < 0)
                return r;

        /* Silently filter out 0.0.0.0 and 127.0.0.53 (our own stub DNS listener) */
        if (!dns_server_address_valid(family, &address))
                return 0;

        /* Filter out duplicates */
        s = dns_server_find(manager_get_first_dns_server(m, type), family, &address, ifindex);
        if (s) {
                /*
                 * Drop the marker. This is used to find the servers
                 * that ceased to exist, see
                 * manager_mark_dns_servers() and
                 * manager_flush_marked_dns_servers().
                 */
                dns_server_move_back_and_unmark(s);
                return 0;
        }

        return dns_server_new(m, NULL, type, NULL, family, &address, ifindex);
}