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
typedef  long long int64_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 long long strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t vlc_strtoi (const char *str)
{
    char *end;
    long long l;

    errno = 0;
    l = strtoll (str, &end, 0);

    if (!errno)
    {
#if (LLONG_MAX > 0x7fffffffffffffffLL)
        if (l > 0x7fffffffffffffffLL
         || l < -0x8000000000000000LL)
            errno = ERANGE;
#endif
        if (*end)
            errno = EINVAL;
    }
    return l;
}