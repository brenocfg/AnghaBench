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
typedef  int /*<<< orphan*/ * DnsResourceKey ;
typedef  int /*<<< orphan*/  DnsAnswerFlags ;
typedef  int /*<<< orphan*/  DnsAnswer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ * const*) ; 
 int dns_answer_copy_by_key (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ * const*,int /*<<< orphan*/ ) ; 
 int dns_answer_remove_by_key (int /*<<< orphan*/ **,int /*<<< orphan*/ * const*) ; 

int dns_answer_move_by_key(DnsAnswer **to, DnsAnswer **from, const DnsResourceKey *key, DnsAnswerFlags or_flags) {
        int r;

        assert(to);
        assert(from);
        assert(key);

        r = dns_answer_copy_by_key(to, *from, key, or_flags);
        if (r < 0)
                return r;

        return dns_answer_remove_by_key(from, key);
}