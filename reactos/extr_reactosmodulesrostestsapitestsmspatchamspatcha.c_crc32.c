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

/* Variables and functions */
 unsigned int* crc_32_tab ; 

unsigned int crc32(unsigned int seed, unsigned char* msg, unsigned int msglen)
{
    unsigned int rem = seed;
    unsigned int i;

    for (i = 0; i < msglen; i++)
    {
        rem = crc_32_tab[(rem ^ msg[i]) & 0xff] ^ (rem >> 8);
    }

    return rem;
}