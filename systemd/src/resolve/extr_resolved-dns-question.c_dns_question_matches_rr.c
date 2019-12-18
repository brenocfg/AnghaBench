#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t n_keys; int /*<<< orphan*/ * keys; } ;
typedef  int /*<<< orphan*/  DnsResourceRecord ;
typedef  TYPE_1__ DnsQuestion ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_resource_key_match_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

int dns_question_matches_rr(DnsQuestion *q, DnsResourceRecord *rr, const char *search_domain) {
        size_t i;
        int r;

        assert(rr);

        if (!q)
                return 0;

        for (i = 0; i < q->n_keys; i++) {
                r = dns_resource_key_match_rr(q->keys[i], rr, search_domain);
                if (r != 0)
                        return r;
        }

        return 0;
}