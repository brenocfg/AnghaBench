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
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ascii_strlower_n (char*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int dns_label_unescape (char const**,char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr (char*,char,int) ; 

int dnssec_canonicalize(const char *n, char *buffer, size_t buffer_max) {
        size_t c = 0;
        int r;

        /* Converts the specified hostname into DNSSEC canonicalized
         * form. */

        if (buffer_max < 2)
                return -ENOBUFS;

        for (;;) {
                r = dns_label_unescape(&n, buffer, buffer_max, 0);
                if (r < 0)
                        return r;
                if (r == 0)
                        break;

                if (buffer_max < (size_t) r + 2)
                        return -ENOBUFS;

                /* The DNSSEC canonical form is not clear on what to
                 * do with dots appearing in labels, the way DNS-SD
                 * does it. Refuse it for now. */

                if (memchr(buffer, '.', r))
                        return -EINVAL;

                ascii_strlower_n(buffer, (size_t) r);
                buffer[r] = '.';

                buffer += r + 1;
                c += r + 1;

                buffer_max -= r + 1;
        }

        if (c <= 0) {
                /* Not even a single label: this is the root domain name */

                assert(buffer_max > 2);
                buffer[0] = '.';
                buffer[1] = 0;

                return 1;
        }

        return (int) c;
}