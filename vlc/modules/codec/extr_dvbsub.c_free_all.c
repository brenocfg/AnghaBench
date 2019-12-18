#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_object_defs; struct TYPE_7__* p_region_defs; scalar_t__ i_region_defs; struct TYPE_7__* p_pixbuf; struct TYPE_7__* p_object_defs; struct TYPE_7__* psz_text; struct TYPE_7__* p_next; } ;
typedef  TYPE_1__ dvbsub_region_t ;
typedef  TYPE_1__ dvbsub_clut_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_9__ {TYPE_1__* p_page; TYPE_1__* p_regions; TYPE_1__* p_cluts; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void free_all( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    dvbsub_region_t *p_reg, *p_reg_next;
    dvbsub_clut_t *p_clut, *p_clut_next;

    /*free( p_sys->p_display ); No longer malloced */

    for( p_clut = p_sys->p_cluts; p_clut != NULL; p_clut = p_clut_next )
    {
        p_clut_next = p_clut->p_next;
        free( p_clut );
    }
    p_sys->p_cluts = NULL;

    for( p_reg = p_sys->p_regions; p_reg != NULL; p_reg = p_reg_next )
    {
        p_reg_next = p_reg->p_next;
        for( int i = 0; i < p_reg->i_object_defs; i++ )
            free( p_reg->p_object_defs[i].psz_text );
        if( p_reg->i_object_defs ) free( p_reg->p_object_defs );
        free( p_reg->p_pixbuf );
        free( p_reg );
    }
    p_sys->p_regions = NULL;

    if( p_sys->p_page )
    {
        if( p_sys->p_page->i_region_defs )
            free( p_sys->p_page->p_region_defs );
        free( p_sys->p_page );
    }
    p_sys->p_page = NULL;
}