#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* scope; } ;
struct TYPE_9__ {TYPE_2__* link; TYPE_1__* manager; } ;
struct TYPE_8__ {int /*<<< orphan*/  dnssec_negative_trust_anchors; } ;
struct TYPE_7__ {int /*<<< orphan*/  trust_anchor; } ;
typedef  TYPE_4__ DnsTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int dns_trust_anchor_lookup_negative (int /*<<< orphan*/ *,char const*) ; 
 int set_contains (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int dns_transaction_negative_trust_anchor_lookup(DnsTransaction *t, const char *name) {
        int r;

        assert(t);

        /* Check whether the specified name is in the NTA
         * database, either in the global one, or the link-local
         * one. */

        r = dns_trust_anchor_lookup_negative(&t->scope->manager->trust_anchor, name);
        if (r != 0)
                return r;

        if (!t->scope->link)
                return 0;

        return set_contains(t->scope->link->dnssec_negative_trust_anchors, name);
}