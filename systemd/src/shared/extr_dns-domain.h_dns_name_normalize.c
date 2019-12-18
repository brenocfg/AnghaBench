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
typedef  int /*<<< orphan*/  DNSLabelFlags ;

/* Variables and functions */
 int dns_name_concat (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static inline int dns_name_normalize(const char *s, DNSLabelFlags flags, char **ret) {
        /* dns_name_concat() normalizes as a side-effect */
        return dns_name_concat(s, NULL, flags, ret);
}