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
 int DNS_LABEL_LDH ; 
 int DNS_LABEL_NO_ESCAPES ; 
 int EINVAL ; 
 int dns_name_concat (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dns_name_is_valid_ldh(const char *s) {
        int r;

        r = dns_name_concat(s, NULL, DNS_LABEL_LDH|DNS_LABEL_NO_ESCAPES, NULL);
        if (r == -EINVAL)
                return 0;
        if (r < 0)
                return r;
        return 1;
}