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
struct TYPE_6__ {scalar_t__ state; int auxiliary_result; struct TYPE_6__* auxiliary_for; } ;
typedef  TYPE_1__ DnsQuery ;

/* Variables and functions */
 int DNS_QUERY_RESTARTED ; 
 scalar_t__ DNS_TRANSACTION_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_query_process_cname (TYPE_1__*) ; 
 int /*<<< orphan*/  resolve_service_all_complete (TYPE_1__*) ; 

__attribute__((used)) static void resolve_service_hostname_complete(DnsQuery *q) {
        int r;

        assert(q);
        assert(q->auxiliary_for);

        if (q->state != DNS_TRANSACTION_SUCCESS) {
                resolve_service_all_complete(q->auxiliary_for);
                return;
        }

        r = dns_query_process_cname(q);
        if (r == DNS_QUERY_RESTARTED) /* This was a cname, and the query was restarted. */
                return;

        /* This auxiliary lookup is finished or failed, let's see if all are finished now. */
        q->auxiliary_result = r;
        resolve_service_all_complete(q->auxiliary_for);
}