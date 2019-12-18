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
typedef  int uint32_t ;

/* Variables and functions */
 int* crc_table ; 
 int crc_table_ready ; 

uint32_t ar_crc32(uint32_t crc32, const unsigned char *data, size_t data_len)
{
    if (!crc_table_ready) {
        uint32_t i, j;
        uint32_t h = 1;
        crc_table[0] = 0;
        for (i = 128; i; i >>= 1) {
            h = (h >> 1) ^ ((h & 1) ? 0xEDB88320 : 0);
            for (j = 0; j < 256; j += 2 * i) {
                crc_table[i + j] = crc_table[j] ^ h;
            }
        }
        crc_table_ready = true;
    }

    crc32 = crc32 ^ 0xFFFFFFFF;
    while (data_len-- > 0) {
        crc32 = (crc32 >> 8) ^ crc_table[(crc32 ^ *data++) & 0xFF];
    }
    return crc32 ^ 0xFFFFFFFF;
}