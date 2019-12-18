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

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_service_name_is_valid (char*) ; 
 scalar_t__ memchr (char const*,int /*<<< orphan*/ ,size_t) ; 
 char* strndupa (char const*,size_t) ; 

__attribute__((used)) static bool dns_service_name_label_is_valid(const char *label, size_t n) {
        char *s;

        assert(label);

        if (memchr(label, 0, n))
                return false;

        s = strndupa(label, n);
        return dns_service_name_is_valid(s);
}