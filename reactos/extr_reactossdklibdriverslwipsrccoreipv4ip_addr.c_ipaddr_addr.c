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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPADDR_NONE ; 
 int /*<<< orphan*/  ip4_addr_get_u32 (int /*<<< orphan*/ *) ; 
 scalar_t__ ipaddr_aton (char const*,int /*<<< orphan*/ *) ; 

u32_t
ipaddr_addr(const char *cp)
{
  ip_addr_t val;

  if (ipaddr_aton(cp, &val)) {
    return ip4_addr_get_u32(&val);
  }
  return (IPADDR_NONE);
}