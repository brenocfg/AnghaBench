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
typedef  TYPE_1__ style_stack_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void PopStyle(style_stack_t** pp_stack)
{
    style_stack_t* p_old = *pp_stack;
    if ( !p_old )
        return;
    *pp_stack = p_old->p_next;
    // Don't free the style, it is now owned by the text_segment_t
    free( p_old );
}