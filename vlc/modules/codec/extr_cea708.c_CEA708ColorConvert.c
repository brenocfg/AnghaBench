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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t CEA708ColorConvert( uint8_t c )
{
    const uint32_t value[4] = {0x00,0x3F,0xF0,0xFF};
    c = c & 0x3F;
    return (value[(c >> 4) & 0x03] << 16) |
           (value[(c >> 2) & 0x03] << 8) |
           value[c & 0x03];
}