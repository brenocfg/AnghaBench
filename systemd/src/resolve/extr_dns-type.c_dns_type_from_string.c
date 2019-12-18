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
struct dns_type_name {int id; } ;

/* Variables and functions */
 unsigned int UINT16_MAX ; 
 int _DNS_TYPE_INVALID ; 
 int /*<<< orphan*/  assert (char const*) ; 
 struct dns_type_name* lookup_dns_type (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_atou (char const*,unsigned int*) ; 
 char* startswith_no_case (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int dns_type_from_string(const char *s) {
        const struct dns_type_name *sc;

        assert(s);

        sc = lookup_dns_type(s, strlen(s));
        if (sc)
                return sc->id;

        s = startswith_no_case(s, "TYPE");
        if (s) {
                unsigned x;

                if (safe_atou(s, &x) >= 0 &&
                    x <= UINT16_MAX)
                        return (int) x;
        }

        return _DNS_TYPE_INVALID;
}