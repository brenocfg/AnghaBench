#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/  p_text; scalar_t__ p_picture; scalar_t__ p_private; } ;
typedef  TYPE_1__ subpicture_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 
 int /*<<< orphan*/  subpicture_region_private_Delete (scalar_t__) ; 
 int /*<<< orphan*/  text_segment_ChainDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 

void subpicture_region_Delete( subpicture_region_t *p_region )
{
    if( !p_region )
        return;

    if( p_region->p_private )
        subpicture_region_private_Delete( p_region->p_private );

    if( p_region->p_picture )
        picture_Release( p_region->p_picture );

    text_segment_ChainDelete( p_region->p_text );
    video_format_Clean( &p_region->fmt );
    free( p_region );
}