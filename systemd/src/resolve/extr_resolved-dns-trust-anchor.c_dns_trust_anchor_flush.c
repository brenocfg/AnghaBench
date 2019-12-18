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
struct TYPE_4__ {int /*<<< orphan*/  negative_by_name; int /*<<< orphan*/  revoked_by_rr; int /*<<< orphan*/  positive_by_key; } ;
typedef  TYPE_1__ DnsTrustAnchor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_answer_unref ; 
 int /*<<< orphan*/  dns_resource_record_unref ; 
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dns_trust_anchor_flush(DnsTrustAnchor *d) {
        assert(d);

        d->positive_by_key = hashmap_free_with_destructor(d->positive_by_key, dns_answer_unref);
        d->revoked_by_rr = set_free_with_destructor(d->revoked_by_rr, dns_resource_record_unref);
        d->negative_by_name = set_free_free(d->negative_by_name);
}