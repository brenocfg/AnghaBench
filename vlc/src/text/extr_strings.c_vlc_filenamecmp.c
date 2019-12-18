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
 int strcoll (char const*,char const*) ; 
 unsigned long long strtoull (char const*,int /*<<< orphan*/ *,int) ; 

int vlc_filenamecmp(const char *a, const char *b)
{
    size_t i;
    char ca, cb;

    /* Attempt to guess if the sorting algorithm should be alphabetic
     * (i.e. collation) or numeric:
     * - If the first mismatching characters are not both digits,
     *   then collation is the only option.
     * - If one of the first mismatching characters is 0 and the other is also
     *   a digit, the comparands are probably left-padded numerical values.
     *   It does not matter which algorithm is used: the zero will be smaller
     *   than non-zero either way.
     * - Otherwise, the comparands are numerical values, and might not be
     *   aligned (i.e. not same order of magnitude). If so, collation would
     *   fail. So numerical comparison is performed. */
    for (i = 0; (ca = a[i]) == (cb = b[i]); i++)
        if (ca == '\0')
            return 0; /* strings are exactly identical */

    if ((unsigned)(ca - '0') > 9 || (unsigned)(cb - '0') > 9)
        return strcoll(a, b);

    unsigned long long ua = strtoull(a + i, NULL, 10);
    unsigned long long ub = strtoull(b + i, NULL, 10);

    /* The number may be identical in two cases:
     * - leading zero (e.g. "012" and "12")
     * - overflow on both sides (#ULLONG_MAX) */
    if (ua == ub)
        return strcoll(a, b);

    return (ua > ub) ? +1 : -1;
}