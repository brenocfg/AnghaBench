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
 char* TAKE_PTR (char const*) ; 
 scalar_t__ ascii_strcasecmp_n (char*,char*,int) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_label_unescape (char const**,char*,int,int /*<<< orphan*/ ) ; 

int dns_name_endswith(const char *name, const char *suffix) {
        const char *n, *s, *saved_n = NULL;
        int r, q;

        assert(name);
        assert(suffix);

        n = name;
        s = suffix;

        for (;;) {
                char ln[DNS_LABEL_MAX], ls[DNS_LABEL_MAX];

                r = dns_label_unescape(&n, ln, sizeof ln, 0);
                if (r < 0)
                        return r;

                if (!saved_n)
                        saved_n = n;

                q = dns_label_unescape(&s, ls, sizeof ls, 0);
                if (q < 0)
                        return q;

                if (r == 0 && q == 0)
                        return true;
                if (r == 0 && saved_n == n)
                        return false;

                if (r != q || ascii_strcasecmp_n(ln, ls, r) != 0) {

                        /* Not the same, let's jump back, and try with the next label again */
                        s = suffix;
                        n = TAKE_PTR(saved_n);
                }
        }
}