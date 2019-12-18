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
struct TYPE_4__ {size_t n_keys; int /*<<< orphan*/ * keys; } ;
typedef  int /*<<< orphan*/  DnsResourceKey ;
typedef  TYPE_1__ DnsQuestion ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_question_add_raw (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dns_resource_key_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dns_question_add(DnsQuestion *q, DnsResourceKey *key) {
        int r;

        assert(key);

        if (!q)
                return -ENOSPC;

        for (size_t i = 0; i < q->n_keys; i++) {
                r = dns_resource_key_equal(q->keys[i], key);
                if (r < 0)
                        return r;
                if (r > 0)
                        return 0;
        }

        return dns_question_add_raw(q, key);
}