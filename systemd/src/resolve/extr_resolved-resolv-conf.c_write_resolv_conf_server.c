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
typedef  unsigned int FILE ;
typedef  unsigned int DnsServer ;
typedef  int /*<<< orphan*/  DnsScope ;

/* Variables and functions */
 unsigned int MAXNS ; 
 int /*<<< orphan*/  assert (unsigned int*) ; 
 int /*<<< orphan*/  dns_scope_is_default_route (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dns_server_scope (unsigned int*) ; 
 char* dns_server_string (unsigned int*) ; 
 int /*<<< orphan*/  fprintf (unsigned int*,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,unsigned int*) ; 
 int /*<<< orphan*/  log_debug (char*,char*) ; 
 int /*<<< orphan*/  log_warning (char*) ; 

__attribute__((used)) static void write_resolv_conf_server(DnsServer *s, FILE *f, unsigned *count) {
        DnsScope *scope;

        assert(s);
        assert(f);
        assert(count);

        if (!dns_server_string(s)) {
                log_warning("Out of memory, or invalid DNS address. Ignoring server.");
                return;
        }

        /* Check if the scope this DNS server belongs to is suitable as 'default' route for lookups; resolv.conf does
         * not have a syntax to express that, so it must not appear as a global name server to avoid routing unrelated
         * domains to it (which is a privacy violation, will most probably fail anyway, and adds unnecessary load) */
        scope = dns_server_scope(s);
        if (scope && !dns_scope_is_default_route(scope)) {
                log_debug("Scope of DNS server %s has only route-only domains, not using as global name server", dns_server_string(s));
                return;
        }

        if (*count == MAXNS)
                fputs("# Too many DNS servers configured, the following entries may be ignored.\n", f);
        (*count)++;

        fprintf(f, "nameserver %s\n", dns_server_string(s));
}