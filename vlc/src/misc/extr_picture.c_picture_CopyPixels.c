#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_planes; TYPE_2__* context; scalar_t__ p; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_7__ {TYPE_2__* (* copy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plane_CopyPixels (scalar_t__,scalar_t__) ; 
 TYPE_2__* stub1 (TYPE_2__*) ; 

void picture_CopyPixels( picture_t *p_dst, const picture_t *p_src )
{
    for( int i = 0; i < p_src->i_planes ; i++ )
        plane_CopyPixels( p_dst->p+i, p_src->p+i );

    assert( p_dst->context == NULL );

    if( p_src->context != NULL )
        p_dst->context = p_src->context->copy( p_src->context );
}