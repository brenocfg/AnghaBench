#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  spu_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* pf_sub_source ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {TYPE_3__* first; } ;
typedef  TYPE_2__ filter_chain_t ;
struct TYPE_8__ {TYPE_1__ filter; struct TYPE_8__* next; } ;
typedef  TYPE_3__ chained_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  spu_PutSubpicture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void filter_chain_SubSource( filter_chain_t *p_chain, spu_t *spu,
                             vlc_tick_t display_date )
{
    for( chained_filter_t *f = p_chain->first; f != NULL; f = f->next )
    {
        filter_t *p_filter = &f->filter;
        subpicture_t *p_subpic = p_filter->pf_sub_source( p_filter, display_date );
        if( p_subpic )
            spu_PutSubpicture( spu, p_subpic );
    }
}