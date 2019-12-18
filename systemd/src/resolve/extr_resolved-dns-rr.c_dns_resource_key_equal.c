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
struct TYPE_5__ {scalar_t__ class; scalar_t__ type; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 int dns_name_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_1__ const*) ; 

int dns_resource_key_equal(const DnsResourceKey *a, const DnsResourceKey *b) {
        int r;

        if (a == b)
                return 1;

        r = dns_name_equal(dns_resource_key_name(a), dns_resource_key_name(b));
        if (r <= 0)
                return r;

        if (a->class != b->class)
                return 0;

        if (a->type != b->type)
                return 0;

        return 1;
}