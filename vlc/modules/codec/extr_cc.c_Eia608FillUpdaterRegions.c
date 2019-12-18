#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {struct TYPE_15__* p_next; } ;
typedef  TYPE_2__ text_segment_t ;
struct TYPE_14__ {float y; } ;
struct TYPE_17__ {TYPE_2__* p_segments; int /*<<< orphan*/  flags; TYPE_1__ origin; int /*<<< orphan*/  inner_align; int /*<<< orphan*/  align; } ;
struct TYPE_16__ {TYPE_4__ region; } ;
typedef  TYPE_3__ subtext_updater_sys_t ;
typedef  TYPE_4__ substext_updater_region_t ;
struct eia608_screen {int /*<<< orphan*/ * row_used; } ;
struct TYPE_18__ {size_t i_screen; struct eia608_screen* screen; } ;
typedef  TYPE_5__ eia608_t ;

/* Variables and functions */
 int EIA608_SCREEN_ROWS ; 
 TYPE_2__* Eia608TextLine (struct eia608_screen*,int) ; 
 int FONT_TO_LINE_HEIGHT_RATIO ; 
 int /*<<< orphan*/  SubpictureUpdaterSysRegionAdd (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* SubpictureUpdaterSysRegionNew () ; 
 int /*<<< orphan*/  UPDT_REGION_ORIGIN_Y_IS_RATIO ; 
 int /*<<< orphan*/  text_segment_ChainDelete (TYPE_2__*) ; 
 TYPE_2__* text_segment_New (char*) ; 

__attribute__((used)) static void Eia608FillUpdaterRegions( subtext_updater_sys_t *p_updater, eia608_t *h )
{
    struct eia608_screen *screen = &h->screen[h->i_screen];
    substext_updater_region_t *p_region = &p_updater->region;
    text_segment_t **pp_last = &p_region->p_segments;
    bool b_newregion = false;

    for( int i = 0; i < EIA608_SCREEN_ROWS; i++ )
    {
        if( !screen->row_used[i] )
            continue;

        text_segment_t *p_segments = Eia608TextLine( screen, i );
        if( p_segments )
        {
            if( b_newregion )
            {
                substext_updater_region_t *p_newregion;
                p_newregion = SubpictureUpdaterSysRegionNew();
                if( !p_newregion )
                {
                    text_segment_ChainDelete( p_segments );
                    return;
                }
                /* Copy defaults */
                p_newregion->align = p_region->align;
                p_newregion->inner_align = p_region->inner_align;
                p_newregion->flags = p_region->flags;
                SubpictureUpdaterSysRegionAdd( p_region, p_newregion );
                p_region = p_newregion;
                pp_last = &p_region->p_segments;
                b_newregion = false;
            }

            if( p_region->p_segments == NULL ) /* First segment in the [new] region */
            {
                p_region->origin.y = (float) i /* start line number */
                                     / (EIA608_SCREEN_ROWS * FONT_TO_LINE_HEIGHT_RATIO);
                p_region->flags |= UPDT_REGION_ORIGIN_Y_IS_RATIO;
            }
            else /* Insert line break between region lines */
            {
                *pp_last = text_segment_New( "\n" );
                if( *pp_last )
                    pp_last = &((*pp_last)->p_next);
            }

            *pp_last = p_segments;
            do { pp_last = &((*pp_last)->p_next); } while ( *pp_last != NULL );
        }
        else
        {
            b_newregion = !!p_region->p_segments;
        }
    }
}