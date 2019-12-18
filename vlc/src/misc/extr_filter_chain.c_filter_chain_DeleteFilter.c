#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fmt_in; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  p_module; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_9__ {int /*<<< orphan*/  obj; TYPE_3__* last; TYPE_3__* first; } ;
typedef  TYPE_2__ filter_chain_t ;
struct TYPE_10__ {int /*<<< orphan*/  mouse; int /*<<< orphan*/  pending; struct TYPE_10__* prev; struct TYPE_10__* next; } ;
typedef  TYPE_3__ chained_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  FilterDeletePictures (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

void filter_chain_DeleteFilter( filter_chain_t *chain, filter_t *filter )
{
    chained_filter_t *chained = (chained_filter_t *)filter;

    /* Remove it from the chain */
    if( chained->prev != NULL )
        chained->prev->next = chained->next;
    else
    {
        assert( chained == chain->first );
        chain->first = chained->next;
    }

    if( chained->next != NULL )
        chained->next->prev = chained->prev;
    else
    {
        assert( chained == chain->last );
        chain->last = chained->prev;
    }

    module_unneed( filter, filter->p_module );

    msg_Dbg( chain->obj, "Filter %p removed from chain", (void *)filter );
    FilterDeletePictures( chained->pending );

    free( chained->mouse );
    es_format_Clean( &filter->fmt_out );
    es_format_Clean( &filter->fmt_in );

    vlc_object_delete(filter);
    /* FIXME: check fmt_in/fmt_out consitency */
}