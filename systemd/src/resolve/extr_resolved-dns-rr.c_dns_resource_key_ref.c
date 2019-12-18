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
struct TYPE_4__ {unsigned int n_ref; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

DnsResourceKey* dns_resource_key_ref(DnsResourceKey *k) {

        if (!k)
                return NULL;

        /* Static/const keys created with DNS_RESOURCE_KEY_CONST will
         * set this to -1, they should not be reffed/unreffed */
        assert(k->n_ref != (unsigned) -1);

        assert(k->n_ref > 0);
        k->n_ref++;

        return k;
}