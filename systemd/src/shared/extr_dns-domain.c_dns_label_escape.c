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
typedef  int uint8_t ;

/* Variables and functions */
 size_t DNS_LABEL_MAX ; 
 int EINVAL ; 
 int ENOBUFS ; 
 scalar_t__ IN_SET (char const,char,char) ; 
 int /*<<< orphan*/  assert (char const*) ; 

int dns_label_escape(const char *p, size_t l, char *dest, size_t sz) {
        char *q;

        /* DNS labels must be between 1 and 63 characters long. A
         * zero-length label does not exist. See RFC 2182, Section
         * 11. */

        if (l <= 0 || l > DNS_LABEL_MAX)
                return -EINVAL;
        if (sz < 1)
                return -ENOBUFS;

        assert(p);
        assert(dest);

        q = dest;
        while (l > 0) {

                if (IN_SET(*p, '.', '\\')) {

                        /* Dot or backslash */

                        if (sz < 3)
                                return -ENOBUFS;

                        *(q++) = '\\';
                        *(q++) = *p;

                        sz -= 2;

                } else if (IN_SET(*p, '_', '-') ||
                           (*p >= '0' && *p <= '9') ||
                           (*p >= 'a' && *p <= 'z') ||
                           (*p >= 'A' && *p <= 'Z')) {

                        /* Proper character */

                        if (sz < 2)
                                return -ENOBUFS;

                        *(q++) = *p;
                        sz -= 1;

                } else {

                        /* Everything else */

                        if (sz < 5)
                                return -ENOBUFS;

                        *(q++) = '\\';
                        *(q++) = '0' + (char) ((uint8_t) *p / 100);
                        *(q++) = '0' + (char) (((uint8_t) *p / 10) % 10);
                        *(q++) = '0' + (char) ((uint8_t) *p % 10);

                        sz -= 4;
                }

                p++;
                l--;
        }

        *q = 0;
        return (int) (q - dest);
}