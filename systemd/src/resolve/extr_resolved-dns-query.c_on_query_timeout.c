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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  DnsQuery ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TRANSACTION_TIMEOUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_query_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_query_timeout(sd_event_source *s, usec_t usec, void *userdata) {
        DnsQuery *q = userdata;

        assert(s);
        assert(q);

        dns_query_complete(q, DNS_TRANSACTION_TIMEOUT);
        return 0;
}