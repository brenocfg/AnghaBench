#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {size_t n_keys; TYPE_3__** keys; } ;
struct TYPE_8__ {TYPE_4__* key; } ;
typedef  TYPE_1__ DnsResourceRecord ;
typedef  TYPE_2__ DnsQuestion ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TYPE_CNAME ; 
 int /*<<< orphan*/  DNS_TYPE_DNAME ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_resource_key_match_cname_or_dname (TYPE_3__*,TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  dns_type_may_redirect (int /*<<< orphan*/ ) ; 

int dns_question_matches_cname_or_dname(DnsQuestion *q, DnsResourceRecord *rr, const char *search_domain) {
        size_t i;
        int r;

        assert(rr);

        if (!q)
                return 0;

        if (!IN_SET(rr->key->type, DNS_TYPE_CNAME, DNS_TYPE_DNAME))
                return 0;

        for (i = 0; i < q->n_keys; i++) {
                /* For a {C,D}NAME record we can never find a matching {C,D}NAME record */
                if (!dns_type_may_redirect(q->keys[i]->type))
                        return 0;

                r = dns_resource_key_match_cname_or_dname(q->keys[i], rr->key, search_domain);
                if (r != 0)
                        return r;
        }

        return 0;
}