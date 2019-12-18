#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_flags; struct TYPE_3__* p_next; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */

__attribute__((used)) static void tag_last_block_with_flag( block_t **out, int i_flag )
{
    block_t *p_last = *out;
    if( p_last )
    {
        while( p_last->p_next )
            p_last = p_last->p_next;
        p_last->i_flags |= i_flag;
    }
}