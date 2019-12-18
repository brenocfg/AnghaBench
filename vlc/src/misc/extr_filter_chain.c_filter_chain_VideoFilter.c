#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* p_next; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_10__ {TYPE_3__* last; int /*<<< orphan*/  first; } ;
typedef  TYPE_2__ filter_chain_t ;
struct TYPE_11__ {int /*<<< orphan*/  next; TYPE_1__* pending; struct TYPE_11__* prev; } ;
typedef  TYPE_3__ chained_filter_t ;

/* Variables and functions */
 TYPE_1__* FilterChainVideoFilter (int /*<<< orphan*/ ,TYPE_1__*) ; 

picture_t *filter_chain_VideoFilter( filter_chain_t *p_chain, picture_t *p_pic )
{
    if( p_pic )
    {
        p_pic = FilterChainVideoFilter( p_chain->first, p_pic );
        if( p_pic )
            return p_pic;
    }
    for( chained_filter_t *b = p_chain->last; b != NULL; b = b->prev )
    {
        p_pic = b->pending;
        if( !p_pic )
            continue;
        b->pending = p_pic->p_next;
        p_pic->p_next = NULL;

        p_pic = FilterChainVideoFilter( b->next, p_pic );
        if( p_pic )
            return p_pic;
    }
    return NULL;
}