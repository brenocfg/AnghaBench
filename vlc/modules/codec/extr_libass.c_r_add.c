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
struct TYPE_4__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_1__ rectangle_t ;

/* Variables and functions */
 void* __MAX (void*,void*) ; 
 void* __MIN (void*,void*) ; 

__attribute__((used)) static void r_add( rectangle_t *r, const rectangle_t *n )
{
    r->x0 = __MIN( r->x0, n->x0 );
    r->y0 = __MIN( r->y0, n->y0 );
    r->x1 = __MAX( r->x1, n->x1 );
    r->y1 = __MAX( r->y1, n->y1 );
}