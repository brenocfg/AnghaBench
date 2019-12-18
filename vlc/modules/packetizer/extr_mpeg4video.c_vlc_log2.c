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

__attribute__((used)) static int vlc_log2( unsigned int v )
{
    int n = 0;
    static const int vlc_log2_table[16] =
    {
        0,0,1,1,2,2,2,2, 3,3,3,3,3,3,3,3
    };

    if( v&0xffff0000 )
    {
        v >>= 16;
        n += 16;
    }
    if( v&0xff00 )
    {
        v >>= 8;
        n += 8;
    }
    if( v&0xf0 )
    {
        v >>= 4;
        n += 4;
    }
    n += vlc_log2_table[v];

    return n;
}