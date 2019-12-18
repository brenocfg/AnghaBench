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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  addr_parse_ip (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_resolve (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int addr_resolve_or_parse_ip(const char *address, IP *to, IP *extra)
{
    if (!addr_resolve(address, to, extra))
        if (!addr_parse_ip(address, to))
            return 0;

    return 1;
}