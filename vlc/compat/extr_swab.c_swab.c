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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;

/* Variables and functions */

void swab( const void *p_src_, void *p_dst_, ssize_t n )
{
    const uint8_t *p_src = p_src_;
    uint8_t *p_dst = p_dst_;

    if( n < 0 )
        return;

    for( ssize_t i = 0; i < n-1; i += 2 )
    {
        uint8_t i_tmp = p_src[i+0];
        p_dst[i+0] = p_src[i+1];
        p_dst[i+1] = i_tmp;
    }
}