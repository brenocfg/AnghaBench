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
 int DNS_LABEL_MAX ; 
 scalar_t__ ascii_strcasecmp_n (char*,char*,int) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_label_unescape (char const**,char*,int,int /*<<< orphan*/ ) ; 

int dns_name_startswith(const char *name, const char *prefix) {
        const char *n, *p;
        int r, q;

        assert(name);
        assert(prefix);

        n = name;
        p = prefix;

        for (;;) {
                char ln[DNS_LABEL_MAX], lp[DNS_LABEL_MAX];

                r = dns_label_unescape(&p, lp, sizeof lp, 0);
                if (r < 0)
                        return r;
                if (r == 0)
                        return true;

                q = dns_label_unescape(&n, ln, sizeof ln, 0);
                if (q < 0)
                        return q;

                if (r != q)
                        return false;
                if (ascii_strcasecmp_n(ln, lp, r) != 0)
                        return false;
        }
}