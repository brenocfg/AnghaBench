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
struct TYPE_6__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_2__*) ;} ;
struct TYPE_7__ {struct TYPE_7__* p_private; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ updater; int /*<<< orphan*/ * p_region; } ;
typedef  TYPE_2__ subpicture_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  subpicture_region_ChainDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 

void subpicture_Delete( subpicture_t *p_subpic )
{
    subpicture_region_ChainDelete( p_subpic->p_region );
    p_subpic->p_region = NULL;

    if( p_subpic->updater.pf_destroy )
        p_subpic->updater.pf_destroy( p_subpic );

    if( p_subpic->p_private )
    {
        video_format_Clean( &p_subpic->p_private->src );
        video_format_Clean( &p_subpic->p_private->dst );
    }

    free( p_subpic->p_private );
    free( p_subpic );
}