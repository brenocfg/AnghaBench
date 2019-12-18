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
typedef  int /*<<< orphan*/  DnsResourceKey ;
typedef  TYPE_1__ DnsQuestion ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int dns_resource_key_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int dns_question_contains(DnsQuestion *a, const DnsResourceKey *k) {
        size_t j;
        int r;

        assert(k);

        if (!a)
                return 0;

        for (j = 0; j < a->n_keys; j++) {
                r = dns_resource_key_equal(a->keys[j], k);
                if (r != 0)
                        return r;
        }

        return 0;
}