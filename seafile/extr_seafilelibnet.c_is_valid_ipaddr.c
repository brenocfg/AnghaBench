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
struct sockaddr_storage {int dummy; } ;

/* Variables and functions */
 scalar_t__ sock_pton (char const*,int /*<<< orphan*/ ,struct sockaddr_storage*) ; 

int
is_valid_ipaddr (const char *addr_str)
{
    struct sockaddr_storage addr;
    if (!addr_str)
        return 0;
    if (sock_pton(addr_str, 0, &addr) < 0)
        return 0;
    return 1;
}