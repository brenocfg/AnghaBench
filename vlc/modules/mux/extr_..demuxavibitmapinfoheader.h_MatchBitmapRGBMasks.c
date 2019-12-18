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
struct TYPE_6__ {scalar_t__ i_rmask; scalar_t__ i_gmask; scalar_t__ i_bmask; } ;
struct TYPE_7__ {scalar_t__ i_codec; TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_8__ {scalar_t__ codec; scalar_t__ i_rmask; scalar_t__ i_gmask; scalar_t__ i_bmask; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 TYPE_3__* bitmap_rgb_masks ; 

__attribute__((used)) static inline bool MatchBitmapRGBMasks( const es_format_t *fmt )
{
    for( size_t i=0; i<ARRAY_SIZE(bitmap_rgb_masks); i++ )
    {
        if( bitmap_rgb_masks[i].codec == fmt->i_codec )
        {
            return fmt->video.i_rmask == bitmap_rgb_masks[i].i_rmask &&
                   fmt->video.i_gmask == bitmap_rgb_masks[i].i_gmask &&
                   fmt->video.i_bmask == bitmap_rgb_masks[i].i_bmask;
        }
    }
    return false;
}