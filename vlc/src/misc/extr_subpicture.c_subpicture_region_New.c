#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_10__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  p_picture; } ;
typedef  TYPE_2__ subpicture_region_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_TEXT ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_NewFromFormat (TYPE_1__ const*) ; 
 TYPE_2__* subpicture_region_NewInternal (TYPE_1__ const*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 

subpicture_region_t *subpicture_region_New( const video_format_t *p_fmt )
{
    subpicture_region_t *p_region =
        subpicture_region_NewInternal( p_fmt );
    if( !p_region )
        return NULL;

    if( p_fmt->i_chroma == VLC_CODEC_TEXT )
        return p_region;

    p_region->p_picture = picture_NewFromFormat( p_fmt );
    if( !p_region->p_picture )
    {
        video_format_Clean( &p_region->fmt );
        free( p_region );
        return NULL;
    }

    return p_region;
}