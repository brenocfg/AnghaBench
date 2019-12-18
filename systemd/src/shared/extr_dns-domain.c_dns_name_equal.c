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

int dns_name_equal(const char *x, const char *y) {
        int r, q;

        assert(x);
        assert(y);

        for (;;) {
                char la[DNS_LABEL_MAX], lb[DNS_LABEL_MAX];

                r = dns_label_unescape(&x, la, sizeof la, 0);
                if (r < 0)
                        return r;

                q = dns_label_unescape(&y, lb, sizeof lb, 0);
                if (q < 0)
                        return q;

                if (r != q)
                        return false;
                if (r == 0)
                        return true;

                if (ascii_strcasecmp_n(la, lb, r) != 0)
                        return false;
        }
}