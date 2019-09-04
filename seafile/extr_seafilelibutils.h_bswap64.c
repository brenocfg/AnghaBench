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
typedef  int val ;
typedef  int uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t
bswap64 (uint64_t val)
{
    uint64_t ret;
    uint8_t *ptr = (uint8_t *)&ret;

    ptr[0]=((val)>>56)&0xFF;
    ptr[1]=((val)>>48)&0xFF;
    ptr[2]=((val)>>40)&0xFF;
    ptr[3]=((val)>>32)&0xFF;
    ptr[4]=((val)>>24)&0xFF;
    ptr[5]=((val)>>16)&0xFF;
    ptr[6]=((val)>>8)&0xFF;
    ptr[7]=(val)&0xFF;

    return ret;
}