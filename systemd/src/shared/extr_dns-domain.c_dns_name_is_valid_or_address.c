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
 int dns_name_is_valid (char const*) ; 
 scalar_t__ in_addr_from_string_auto (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 

int dns_name_is_valid_or_address(const char *name) {
        /* Returns > 0 if the specified name is either a valid IP address formatted as string or a valid DNS name */

        if (isempty(name))
                return 0;

        if (in_addr_from_string_auto(name, NULL, NULL) >= 0)
                return 1;

        return dns_name_is_valid(name);
}