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
typedef  size_t uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* crc16tab ; 

uint32_t
hash_crc16(const char *key, size_t key_length)
{
    uint64_t x;
    uint32_t crc = 0;

    for (x=0; x < key_length; x++) {
        crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ *key++) & 0x00ff];
    }

    return crc;
}