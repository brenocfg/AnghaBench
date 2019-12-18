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
struct TYPE_4__ {scalar_t__ y1; scalar_t__ y0; scalar_t__ x1; scalar_t__ x0; } ;
typedef  TYPE_1__ rectangle_t ;

/* Variables and functions */
 scalar_t__ __MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ __MIN (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool r_overlap( const rectangle_t *a, const rectangle_t *b, int i_dx, int i_dy )
{
    return  __MAX(a->x0-i_dx, b->x0) < __MIN( a->x1+i_dx, b->x1 ) &&
            __MAX(a->y0-i_dy, b->y0) < __MIN( a->y1+i_dy, b->y1 );
}