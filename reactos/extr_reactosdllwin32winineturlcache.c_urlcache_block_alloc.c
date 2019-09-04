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
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int CHAR_BIT ; 

__attribute__((used)) static inline void urlcache_block_alloc(BYTE *allocation_table, DWORD block_number)
{
    BYTE mask = 1 << (block_number%CHAR_BIT);
    allocation_table[block_number/CHAR_BIT] |= mask;
}