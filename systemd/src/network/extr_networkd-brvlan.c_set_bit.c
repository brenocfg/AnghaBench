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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int BRIDGE_VLAN_BITMAP_MAX ; 
 unsigned int UINT32_C (int) ; 

__attribute__((used)) static void set_bit(unsigned nr, uint32_t *addr) {
        if (nr < BRIDGE_VLAN_BITMAP_MAX)
                addr[nr / 32] |= (UINT32_C(1) << (nr % 32));
}