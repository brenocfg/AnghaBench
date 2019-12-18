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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int fw_add_local_dnat(
                bool add,
                int af,
                int protocol,
                const char *in_interface,
                const union in_addr_union *source,
                unsigned source_prefixlen,
                const union in_addr_union *destination,
                unsigned destination_prefixlen,
                uint16_t local_port,
                const union in_addr_union *remote,
                uint16_t remote_port,
                const union in_addr_union *previous_remote) {
        return -EOPNOTSUPP;
}