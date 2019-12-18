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
ip_addr_netcmp(struct ip_addr *addr1, struct ip_addr *addr2,
                struct ip_addr *mask)
{
  return((addr1->addr[0] & mask->addr[0]) == (addr2->addr[0] & mask->addr[0]) &&
         (addr1->addr[1] & mask->addr[1]) == (addr2->addr[1] & mask->addr[1]) &&
         (addr1->addr[2] & mask->addr[2]) == (addr2->addr[2] & mask->addr[2]) &&
         (addr1->addr[3] & mask->addr[3]) == (addr2->addr[3] & mask->addr[3]));
        
}