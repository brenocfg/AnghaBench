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
struct TYPE_7__ {int /*<<< orphan*/  region; } ;
typedef  TYPE_2__ subtext_updater_sys_t ;
typedef  int /*<<< orphan*/  substext_updater_region_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
struct TYPE_8__ {TYPE_1__ updater; } ;
typedef  TYPE_3__ subpicture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  SubpictureUpdaterSysRegionAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SubpictureUpdaterSysRegionNew () ; 
 TYPE_3__* decoder_NewSubpictureText (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CreateSpuOrNewUpdaterRegion( decoder_t *p_dec,
                                         subpicture_t **pp_spu,
                                         substext_updater_region_t **pp_updtregion )
{
    if( *pp_spu == NULL )
    {
        *pp_spu = decoder_NewSubpictureText( p_dec );
        if( *pp_spu )
        {
            subtext_updater_sys_t *p_spusys = (*pp_spu)->updater.p_sys;
            *pp_updtregion = &p_spusys->region;
        }
    }
    else
    {
        substext_updater_region_t *p_new =
                                SubpictureUpdaterSysRegionNew( );
        if( p_new )
        {
            SubpictureUpdaterSysRegionAdd( *pp_updtregion, p_new );
            *pp_updtregion = p_new;
        }
    }
}