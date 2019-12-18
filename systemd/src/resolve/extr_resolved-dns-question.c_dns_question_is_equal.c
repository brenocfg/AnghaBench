#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t n_keys; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ DnsQuestion ;

/* Variables and functions */
 int dns_question_contains (TYPE_1__*,int /*<<< orphan*/ ) ; 

int dns_question_is_equal(DnsQuestion *a, DnsQuestion *b) {
        size_t j;
        int r;

        if (a == b)
                return 1;

        if (!a)
                return !b || b->n_keys == 0;
        if (!b)
                return a->n_keys == 0;

        /* Checks if all keys in a are also contained b, and vice versa */

        for (j = 0; j < a->n_keys; j++) {
                r = dns_question_contains(b, a->keys[j]);
                if (r <= 0)
                        return r;
        }

        for (j = 0; j < b->n_keys; j++) {
                r = dns_question_contains(a, b->keys[j]);
                if (r <= 0)
                        return r;
        }

        return 1;
}