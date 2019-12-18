#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ i_priority; } ;
typedef  TYPE_1__ input_item_slave_t ;

/* Variables and functions */

__attribute__((used)) static int SlaveCompare(const void *a, const void *b)
{
    const input_item_slave_t *p_slave0 = *((const input_item_slave_t **) a);
    const input_item_slave_t *p_slave1 = *((const input_item_slave_t **) b);

    if( p_slave0 == NULL || p_slave1 == NULL )
    {
        /* Put NULL (or rejected) subs at the end */
        return p_slave0 == NULL ? 1 : p_slave1 == NULL ? -1 : 0;
    }

    if( p_slave0->i_priority > p_slave1->i_priority )
        return -1;

    if( p_slave0->i_priority < p_slave1->i_priority )
        return 1;

    return 0;
}