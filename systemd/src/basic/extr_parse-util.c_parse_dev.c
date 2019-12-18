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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_MAJOR_VALID (unsigned int) ; 
 int /*<<< orphan*/  DEVICE_MINOR_VALID (unsigned int) ; 
 int /*<<< orphan*/  DIGITS ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  makedev (unsigned int,unsigned int) ; 
 int safe_atou (char const*,unsigned int*) ; 
 char* strndupa (char const*,size_t) ; 
 size_t strspn (char const*,int /*<<< orphan*/ ) ; 

int parse_dev(const char *s, dev_t *ret) {
        const char *major;
        unsigned x, y;
        size_t n;
        int r;

        n = strspn(s, DIGITS);
        if (n == 0)
                return -EINVAL;
        if (s[n] != ':')
                return -EINVAL;

        major = strndupa(s, n);
        r = safe_atou(major, &x);
        if (r < 0)
                return r;

        r = safe_atou(s + n + 1, &y);
        if (r < 0)
                return r;

        if (!DEVICE_MAJOR_VALID(x) || !DEVICE_MINOR_VALID(y))
                return -ERANGE;

        *ret = makedev(x, y);
        return 0;
}