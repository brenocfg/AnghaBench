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
 int /*<<< orphan*/  PREFIXLEN_FULL ; 
 int in_addr_prefix_from_string_auto_internal (char const*,int /*<<< orphan*/ ,int*,union in_addr_union*,unsigned char*) ; 

__attribute__((used)) static inline int in_addr_prefix_from_string_auto(const char *p, int *ret_family, union in_addr_union *ret_prefix, unsigned char *ret_prefixlen) {
        return in_addr_prefix_from_string_auto_internal(p, PREFIXLEN_FULL, ret_family, ret_prefix, ret_prefixlen);
}