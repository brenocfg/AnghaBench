#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  margin_ratio; int /*<<< orphan*/  region; } ;
typedef  TYPE_2__ subtext_updater_sys_t ;
typedef  int /*<<< orphan*/  substext_updater_region_t ;
struct TYPE_11__ {TYPE_2__* p_sys; } ;
struct TYPE_13__ {int b_ephemer; int b_absolute; int b_subtitle; scalar_t__ i_stop; scalar_t__ i_start; TYPE_1__ updater; } ;
typedef  TYPE_3__ subpicture_t ;
struct TYPE_14__ {scalar_t__ b_visible; scalar_t__ b_defined; } ;
typedef  TYPE_4__ cea708_window_t ;
struct TYPE_15__ {scalar_t__ i_clock; TYPE_4__* window; int /*<<< orphan*/  p_dec; } ;
typedef  TYPE_5__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708SpuConvert (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CEA708_SCREEN_SAFE_MARGIN_RATIO ; 
 size_t CEA708_WINDOWS_COUNT ; 
 scalar_t__ CEA708_Window_RowCount (TYPE_4__*) ; 
 int /*<<< orphan*/  SubpictureUpdaterSysRegionAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SubpictureUpdaterSysRegionNew () ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 TYPE_3__* decoder_NewSubpictureText (int /*<<< orphan*/ ) ; 

__attribute__((used)) static subpicture_t *CEA708_BuildSubtitle( cea708_t *p_cea708 )
{
    subpicture_t *p_spu = decoder_NewSubpictureText( p_cea708->p_dec );
    if( !p_spu )
        return NULL;

    subtext_updater_sys_t *p_spu_sys = p_spu->updater.p_sys;
    substext_updater_region_t *p_region = &p_spu_sys->region;

    p_spu_sys->margin_ratio = CEA708_SCREEN_SAFE_MARGIN_RATIO;

    bool first = true;

    for(size_t i=0; i<CEA708_WINDOWS_COUNT; i++)
    {
        cea708_window_t *p_w = &p_cea708->window[i];
        if( p_w->b_defined && p_w->b_visible && CEA708_Window_RowCount( p_w ) )
        {
            if( !first )
            {
                substext_updater_region_t *p_newregion =
                        SubpictureUpdaterSysRegionNew();
                if( p_newregion == NULL )
                    break;
                SubpictureUpdaterSysRegionAdd( p_region, p_newregion );
                p_region = p_newregion;
            }
            first = false;

            /* Fill region */
            CEA708SpuConvert( p_w, p_region );
        }
    }

    p_spu->i_start    = p_cea708->i_clock;
    p_spu->i_stop     = p_cea708->i_clock + VLC_TICK_FROM_SEC(10);   /* 10s max */

    p_spu->b_ephemer  = true;
    p_spu->b_absolute = false;
    p_spu->b_subtitle = true;

    return p_spu;
}