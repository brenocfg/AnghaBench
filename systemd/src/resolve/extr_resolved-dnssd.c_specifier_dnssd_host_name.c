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
struct TYPE_4__ {struct TYPE_4__* llmnr_hostname; struct TYPE_4__* manager; } ;
typedef  TYPE_1__ DnssdService ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* strdup (TYPE_1__*) ; 

__attribute__((used)) static int specifier_dnssd_host_name(char specifier, const void *data, const void *userdata, char **ret) {
        DnssdService *s  = (DnssdService *) userdata;
        char *n;

        assert(s);
        assert(s->manager);
        assert(s->manager->llmnr_hostname);

        n = strdup(s->manager->llmnr_hostname);
        if (!n)
                return -ENOMEM;

        *ret = n;
        return 0;
}