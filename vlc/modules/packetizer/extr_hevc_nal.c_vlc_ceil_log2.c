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
typedef  unsigned int uint8_t ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int clz (unsigned int) ; 

__attribute__((used)) static inline uint8_t vlc_ceil_log2( uint32_t val )
{
    uint8_t n = 31 - clz(val);
    if (((unsigned)1 << n) != val)
        n++;
    return n;
}