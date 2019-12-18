#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ text_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  text_segment_Delete (TYPE_1__*) ; 

void text_segment_ChainDelete( text_segment_t *segment )
{
    while( segment != NULL )
    {
        text_segment_t *p_next = segment->p_next;

        text_segment_Delete( segment );

        segment = p_next;
    }
}