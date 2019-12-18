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
struct TYPE_3__ {char* _name; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 scalar_t__ dns_name_is_root (char const*) ; 

const char* dns_resource_key_name(const DnsResourceKey *key) {
        const char *name;

        if (!key)
                return NULL;

        if (key->_name)
                name = key->_name;
        else
                name = (char*) key + sizeof(DnsResourceKey);

        if (dns_name_is_root(name))
                return ".";
        else
                return name;
}