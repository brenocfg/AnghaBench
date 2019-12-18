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
struct TYPE_5__ {int /*<<< orphan*/  class; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dns_name_compare_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_1__ const*) ; 

__attribute__((used)) static int dns_resource_key_compare_func(const DnsResourceKey *x, const DnsResourceKey *y) {
        int ret;

        ret = dns_name_compare_func(dns_resource_key_name(x), dns_resource_key_name(y));
        if (ret != 0)
                return ret;

        ret = CMP(x->type, y->type);
        if (ret != 0)
                return ret;

        ret = CMP(x->class, y->class);
        if (ret != 0)
                return ret;

        return 0;
}