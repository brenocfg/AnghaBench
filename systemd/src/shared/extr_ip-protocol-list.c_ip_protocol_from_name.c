#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ip_protocol_name {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (char const*) ; 
 struct ip_protocol_name* lookup_ip_protocol (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int ip_protocol_from_name(const char *name) {
        const struct ip_protocol_name *sc;

        assert(name);

        sc = lookup_ip_protocol(name, strlen(name));
        if (!sc)
                return -EINVAL;

        return sc->id;
}