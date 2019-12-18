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
typedef  scalar_t__ locale_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LC_MESSAGES_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  freelocale (scalar_t__) ; 
 scalar_t__ newlocale (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 char* strerror_l (int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const char *vlc_strerror_l(int errnum, const char *lname)
{
    int saved_errno = errno;
    locale_t loc = newlocale(LC_MESSAGES_MASK, lname, (locale_t)0);

    if (unlikely(loc == (locale_t)0))
    {
        if (errno == ENOENT) /* fallback to POSIX locale */
            loc = newlocale(LC_MESSAGES_MASK, "C", (locale_t)0);

        if (unlikely(loc == (locale_t)0))
        {
            assert(errno != EINVAL && errno != ENOENT);
            errno = saved_errno;
            return "Error message unavailable";
        }
        errno = saved_errno;
    }

    const char *buf = strerror_l(errnum, loc);

    freelocale(loc);
    return buf;
}