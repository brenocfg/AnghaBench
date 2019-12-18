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
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  answer; } ;
typedef  TYPE_1__ DnsTransaction ;
typedef  int /*<<< orphan*/  DnsAnswerFlags ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_answer_find_cname_or_dname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dns_answer_match_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dns_transaction_has_positive_answer(DnsTransaction *t, DnsAnswerFlags *flags) {
        int r;

        assert(t);

        /* Checks whether the answer is positive, i.e. either a direct
         * answer to the question, or a CNAME/DNAME for it */

        r = dns_answer_match_key(t->answer, t->key, flags);
        if (r != 0)
                return r;

        r = dns_answer_find_cname_or_dname(t->answer, t->key, NULL, flags);
        if (r != 0)
                return r;

        return false;
}