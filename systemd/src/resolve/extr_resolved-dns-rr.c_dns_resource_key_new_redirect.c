#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {scalar_t__ type; int /*<<< orphan*/  class; TYPE_2__ dname; struct TYPE_18__ const* key; TYPE_1__ cname; } ;
typedef  TYPE_3__ DnsResourceRecord ;
typedef  TYPE_3__ DnsResourceKey ;

/* Variables and functions */
 scalar_t__ DNS_TYPE_CNAME ; 
 int /*<<< orphan*/  DNS_TYPE_DNAME ; 
 TYPE_3__ const* IN_SET (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 int dns_name_change_suffix (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_3__ const*) ; 
 TYPE_3__* dns_resource_key_new (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* dns_resource_key_new_consume (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 TYPE_3__* dns_resource_key_ref (TYPE_3__*) ; 
 TYPE_3__* mfree (char*) ; 

DnsResourceKey* dns_resource_key_new_redirect(const DnsResourceKey *key, const DnsResourceRecord *cname) {
        int r;

        assert(key);
        assert(cname);

        assert(IN_SET(cname->key->type, DNS_TYPE_CNAME, DNS_TYPE_DNAME));

        if (cname->key->type == DNS_TYPE_CNAME)
                return dns_resource_key_new(key->class, key->type, cname->cname.name);
        else {
                DnsResourceKey *k;
                char *destination = NULL;

                r = dns_name_change_suffix(dns_resource_key_name(key), dns_resource_key_name(cname->key), cname->dname.name, &destination);
                if (r < 0)
                        return NULL;
                if (r == 0)
                        return dns_resource_key_ref((DnsResourceKey*) key);

                k = dns_resource_key_new_consume(key->class, key->type, destination);
                if (!k)
                        return mfree(destination);

                return k;
        }
}