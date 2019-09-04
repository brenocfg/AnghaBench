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
typedef  int u8_t ;
struct ip_addr {int* addr; } ;

/* Variables and functions */

u8_t
ip_addr_isany(struct ip_addr *addr)
{
  if (addr == NULL) return 1;
  return((addr->addr[0] | addr->addr[1] | addr->addr[2] | addr->addr[3]) == 0);
}