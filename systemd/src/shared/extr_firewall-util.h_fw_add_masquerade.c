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
typedef  union in_addr_union {int dummy; } in_addr_union ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int fw_add_masquerade(
                bool add,
                int af,
                int protocol,
                const union in_addr_union *source,
                unsigned source_prefixlen,
                const char *out_interface,
                const union in_addr_union *destination,
                unsigned destination_prefixlen) {
        return -EOPNOTSUPP;
}