#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_items; int /*<<< orphan*/ * pp_items; int /*<<< orphan*/ * p_rd; } ;
typedef  TYPE_1__ libvlc_renderer_discoverer_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_rd_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_renderer_item_release (int /*<<< orphan*/ ) ; 

void
libvlc_renderer_discoverer_stop( libvlc_renderer_discoverer_t *p_lrd )
{
    if( p_lrd->p_rd != NULL )
    {
        vlc_rd_release( p_lrd->p_rd );
        p_lrd->p_rd = NULL;
    }

    for( int i = 0; i < p_lrd->i_items; ++i )
        vlc_renderer_item_release( p_lrd->pp_items[i] );
    TAB_CLEAN( p_lrd->i_items, p_lrd->pp_items );
}