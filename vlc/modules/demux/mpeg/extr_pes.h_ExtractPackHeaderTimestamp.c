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
typedef  int stime_t ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static inline stime_t ExtractPackHeaderTimestamp( const uint8_t *p_data )
{
    return ((int64_t)(p_data[ 0]&0x38 ) << 27)|
            ((int64_t)(p_data[0]&0x03 ) << 28)|
             (int64_t)(p_data[1] << 20)|
            ((int64_t)(p_data[2]&0xf8 ) << 12)|
            ((int64_t)(p_data[2]&0x03 ) << 13)|
             (int64_t)(p_data[3] << 5) |
             (int64_t)(p_data[4] >> 3);
}