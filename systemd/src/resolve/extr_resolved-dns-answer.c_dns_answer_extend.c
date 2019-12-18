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
typedef  int /*<<< orphan*/  DnsAnswer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int dns_answer_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dns_answer_unref (int /*<<< orphan*/ *) ; 

int dns_answer_extend(DnsAnswer **a, DnsAnswer *b) {
        DnsAnswer *merged;
        int r;

        assert(a);

        r = dns_answer_merge(*a, b, &merged);
        if (r < 0)
                return r;

        dns_answer_unref(*a);
        *a = merged;

        return 0;
}