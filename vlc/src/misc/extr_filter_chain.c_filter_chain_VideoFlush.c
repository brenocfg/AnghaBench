#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_4__ {TYPE_2__* first; } ;
typedef  TYPE_1__ filter_chain_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pending; int /*<<< orphan*/  filter; struct TYPE_5__* next; } ;
typedef  TYPE_2__ chained_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  FilterDeletePictures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_Flush (int /*<<< orphan*/ *) ; 

void filter_chain_VideoFlush( filter_chain_t *p_chain )
{
    for( chained_filter_t *f = p_chain->first; f != NULL; f = f->next )
    {
        filter_t *p_filter = &f->filter;

        FilterDeletePictures( f->pending );
        f->pending = NULL;

        filter_Flush( p_filter );
    }
}