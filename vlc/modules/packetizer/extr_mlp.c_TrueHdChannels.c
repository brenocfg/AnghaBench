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

/* Variables and functions */

__attribute__((used)) static int TrueHdChannels( int i_map )
{
    static const uint8_t pu_thd[13] =
    {
         2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1
    };
    int i_count = 0;

    for( int i = 0; i < 13; i++ )
    {
        if( i_map & (1<<i) )
            i_count += pu_thd[i];
    }
    return i_count;
}