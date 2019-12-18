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
typedef  int /*<<< orphan*/  const uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* hxxx_ep3b_to_rbsp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int*,int) ; 

__attribute__((used)) static size_t hxxx_ep3b_total_size( const uint8_t *p, const uint8_t *p_end )
{
    /* compute final size */
    unsigned i_prev = 0;
    size_t i = 0;
    while( p < p_end )
    {
        uint8_t *n = hxxx_ep3b_to_rbsp( (uint8_t *)p, (uint8_t *)p_end, &i_prev, 1 );
        if( n > p )
            ++i;
        p = n;
    }
    return i;
}