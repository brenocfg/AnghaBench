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
typedef  int /*<<< orphan*/  lb ;
typedef  int /*<<< orphan*/  la ;

/* Variables and functions */
 int CMP (int,int) ; 
 int DNS_LABEL_MAX ; 
 int ascii_strcasecmp_nn (char*,int,char*,int) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int dns_label_unescape_suffix (char const*,char const**,char*,int) ; 
 int strlen (char const*) ; 

int dns_name_compare_func(const char *a, const char *b) {
        const char *x, *y;
        int r, q;

        assert(a);
        assert(b);

        x = a + strlen(a);
        y = b + strlen(b);

        for (;;) {
                char la[DNS_LABEL_MAX], lb[DNS_LABEL_MAX];

                if (x == NULL && y == NULL)
                        return 0;

                r = dns_label_unescape_suffix(a, &x, la, sizeof(la));
                q = dns_label_unescape_suffix(b, &y, lb, sizeof(lb));
                if (r < 0 || q < 0)
                        return CMP(r, q);

                r = ascii_strcasecmp_nn(la, r, lb, q);
                if (r != 0)
                        return r;
        }
}