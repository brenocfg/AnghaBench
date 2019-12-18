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

/* Variables and functions */

__attribute__((used)) static void YUV422Mirror2Pixels( uint8_t* p_dst, uint8_t *p_src,
                                bool b_y_is_odd )
{
    if ( b_y_is_odd )
    {
        /* swap Y components */
        *p_dst = *( p_src + 2 );
        *( p_dst + 2 ) = *p_src;
        /* copy Cb and Cr components */
        *( p_dst + 1 ) = *( p_src + 1 );
        *( p_dst + 3 ) = *( p_src + 3 );
    }
    else{
        /* swap Y components */
        *( p_dst + 1 )= *( p_src + 3 );
        *( p_dst + 3 ) = *( p_src + 1);
        /* copy Cb and Cr components */
        *p_dst = *( p_src + 2 );
        *( p_dst + 2 ) = *p_src;
    }
}