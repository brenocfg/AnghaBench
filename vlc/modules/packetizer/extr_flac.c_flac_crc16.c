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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int* flac_crc16_table ; 

__attribute__((used)) static uint16_t flac_crc16(uint16_t crc, uint8_t byte)
{
    return (crc << 8) ^ flac_crc16_table[(crc >> 8) ^ byte];
}