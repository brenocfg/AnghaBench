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
typedef  int /*<<< orphan*/ * DnsResourceRecord ;
typedef  int /*<<< orphan*/  DnsAnswerFlags ;
typedef  int /*<<< orphan*/  DnsAnswer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int dns_answer_add (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int dns_answer_reserve_or_clone (int /*<<< orphan*/ **,int) ; 

int dns_answer_add_extend(DnsAnswer **a, DnsResourceRecord *rr, int ifindex, DnsAnswerFlags flags) {
        int r;

        assert(a);
        assert(rr);

        r = dns_answer_reserve_or_clone(a, 1);
        if (r < 0)
                return r;

        return dns_answer_add(*a, rr, ifindex, flags);
}