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
struct TYPE_5__ {unsigned int n_ref; struct TYPE_5__* _name; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

DnsResourceKey* dns_resource_key_unref(DnsResourceKey *k) {
        if (!k)
                return NULL;

        assert(k->n_ref != (unsigned) -1);
        assert(k->n_ref > 0);

        if (k->n_ref == 1) {
                free(k->_name);
                free(k);
        } else
                k->n_ref--;

        return NULL;
}