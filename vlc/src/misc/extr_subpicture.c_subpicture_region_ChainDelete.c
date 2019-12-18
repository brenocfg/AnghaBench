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
typedef  TYPE_1__ subpicture_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  subpicture_region_Delete (TYPE_1__*) ; 

void subpicture_region_ChainDelete( subpicture_region_t *p_head )
{
    while( p_head )
    {
        subpicture_region_t *p_next = p_head->p_next;

        subpicture_region_Delete( p_head );

        p_head = p_next;
    }
}