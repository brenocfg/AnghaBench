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
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static inline int16_t FloatToInt16( float f )
{
    if( f >= 1.0 )
        return 32767;
    else if( f < -1.0 )
        return -32768;
    else
        return (int16_t)( f * 32768.0 );
}