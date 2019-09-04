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
struct in_addr {scalar_t__ s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ inet_addr (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int adns_inet_aton(const char *cp, struct in_addr *inp)
{
    if (!cp || !*cp || !inp)
    {
        errno = EINVAL;
        return -1; 
    }

    if (!strcmp(cp, "255.255.255.255"))
    {
        // Special case
        inp->s_addr = INADDR_NONE;
        return 0;
    }

	inp->s_addr = inet_addr(cp);
    return (inp->s_addr == INADDR_NONE) ? -1 : 0;
}