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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t* flac_crc8_table ; 

__attribute__((used)) static uint8_t flac_crc8(const uint8_t *data, size_t len)
{
    uint8_t crc = 0;

    while (len--)
        crc = flac_crc8_table[crc ^ *data++];

    return crc;
}