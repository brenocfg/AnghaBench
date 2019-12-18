#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ i_chroma; int /*<<< orphan*/ * p_palette; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_11__ {int den; int num; } ;
struct TYPE_10__ {int den; int num; } ;
struct TYPE_13__ {int i_alpha; int b_balanced_text; TYPE_3__ fmt; TYPE_2__ zoom_v; TYPE_1__ zoom_h; } ;
typedef  TYPE_4__ subpicture_region_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_YUVP ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_3__*,TYPE_3__ const*) ; 

subpicture_region_t * subpicture_region_NewInternal( const video_format_t *p_fmt )
{
    subpicture_region_t *p_region = calloc( 1, sizeof(*p_region ) );
    if( !p_region )
        return NULL;

    p_region->zoom_h.den = p_region->zoom_h.num = 1;
    p_region->zoom_v.den = p_region->zoom_v.num = 1;

    if ( p_fmt->i_chroma == VLC_CODEC_YUVP )
    {
        video_format_Copy( &p_region->fmt, p_fmt );
        /* YUVP should have a palette */
        if( p_region->fmt.p_palette == NULL )
        {
            p_region->fmt.p_palette = calloc( 1, sizeof(*p_region->fmt.p_palette) );
            if( p_region->fmt.p_palette == NULL )
            {
                free( p_region );
                return NULL;
            }
        }
    }
    else
    {
        p_region->fmt = *p_fmt;
        p_region->fmt.p_palette = NULL;
    }

    p_region->i_alpha = 0xff;
    p_region->b_balanced_text = true;

    return p_region;
}