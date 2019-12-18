#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_18__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_21__ {TYPE_5__ extent; TYPE_3__ origin; int /*<<< orphan*/  flags; scalar_t__ p_next; } ;
struct TYPE_16__ {int /*<<< orphan*/  i_bytes; int /*<<< orphan*/  p_bytes; } ;
struct TYPE_23__ {TYPE_6__ updt; TYPE_1__ bgbitmap; } ;
typedef  TYPE_8__ ttml_region_t ;
struct TYPE_19__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_24__ {TYPE_4__ extent; TYPE_2__ origin; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_9__ ttml_image_updater_region_t ;
struct TYPE_22__ {int /*<<< orphan*/  p_sys; } ;
struct TYPE_15__ {TYPE_7__ updater; } ;
typedef  TYPE_10__ subpicture_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 scalar_t__ EXTENT_Y_IS_RATIO ; 
 scalar_t__ ORIGIN_X_IS_RATIO ; 
 int /*<<< orphan*/  TTML_ImageSpuAppendRegion (int /*<<< orphan*/ ,TYPE_9__*) ; 
 TYPE_9__* TTML_ImageUpdaterRegionNew (int /*<<< orphan*/ *) ; 
 scalar_t__ UPDT_REGION_EXTENT_Y_IS_RATIO ; 
 scalar_t__ UPDT_REGION_ORIGIN_X_IS_RATIO ; 
 int /*<<< orphan*/ * picture_CreateFromPNG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 

__attribute__((used)) static void TTMLRegionsToSpuBitmapRegions( decoder_t *p_dec, subpicture_t *p_spu,
                                           ttml_region_t *p_regions )
{
    /* Create region update info from each ttml region */
    for( ttml_region_t *p_region = p_regions;
                        p_region; p_region = (ttml_region_t *) p_region->updt.p_next )
    {
        picture_t *p_pic = picture_CreateFromPNG( p_dec, p_region->bgbitmap.p_bytes,
                                                         p_region->bgbitmap.i_bytes );
        if( p_pic )
        {
            ttml_image_updater_region_t *r = TTML_ImageUpdaterRegionNew( p_pic );
            if( !r )
            {
                picture_Release( p_pic );
                continue;
            }
            /* use text updt values/flags for ease */
            static_assert((int)UPDT_REGION_ORIGIN_X_IS_RATIO == (int)ORIGIN_X_IS_RATIO,
                          "flag enums values differs");
            static_assert((int)UPDT_REGION_EXTENT_Y_IS_RATIO == (int)EXTENT_Y_IS_RATIO,
                          "flag enums values differs");
            r->i_flags = p_region->updt.flags;
            r->origin.x = p_region->updt.origin.x;
            r->origin.y = p_region->updt.origin.y;
            r->extent.x = p_region->updt.extent.x;
            r->extent.y = p_region->updt.extent.y;
            TTML_ImageSpuAppendRegion( p_spu->updater.p_sys, r );
        }
    }
}