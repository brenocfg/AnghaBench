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
struct TYPE_4__ {struct TYPE_4__* p_father; struct TYPE_4__* p_last; struct TYPE_4__* p_next; struct TYPE_4__* p_first; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */

__attribute__((used)) static void MP4_BoxAddChild( MP4_Box_t *p_parent, MP4_Box_t *p_childbox )
{
    if( !p_parent->p_first )
            p_parent->p_first = p_childbox;
    else
            p_parent->p_last->p_next = p_childbox;
    p_parent->p_last = p_childbox;
    p_childbox->p_father = p_parent;
}