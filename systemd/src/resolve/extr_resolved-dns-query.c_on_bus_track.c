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
typedef  int /*<<< orphan*/  sd_bus_track ;
typedef  int /*<<< orphan*/  DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TRANSACTION_ABORTED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_query_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int on_bus_track(sd_bus_track *t, void *userdata) {
        DnsQuery *q = userdata;

        assert(t);
        assert(q);

        log_debug("Client of active query vanished, aborting query.");
        dns_query_complete(q, DNS_TRANSACTION_ABORTED);
        return 0;
}