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
struct TYPE_3__ {int i_align; int i_x; int i_y; } ;
typedef  TYPE_1__ subpicture_region_t ;

/* Variables and functions */
 int ATTRIBUTE_ALIGNMENT ; 
 int ATTRIBUTE_X ; 
 int ATTRIBUTE_X_PERCENT ; 
 int ATTRIBUTE_Y ; 
 int ATTRIBUTE_Y_PERCENT ; 
 int ParsePositionAttributeList (char*,int*,int*,int*) ; 

__attribute__((used)) static void SetupPositions( subpicture_region_t *p_region, char *psz_subtitle )
{
    int           i_mask = 0;
    int           i_align;
    int           i_x, i_y;

    i_mask = ParsePositionAttributeList( psz_subtitle, &i_align, &i_x, &i_y );

    if( i_mask & ATTRIBUTE_ALIGNMENT )
        p_region->i_align = i_align;

    /* TODO: Setup % based offsets properly, without adversely affecting
     *       everything else in vlc. Will address with separate patch, to
     *       prevent this one being any more complicated.
     */
    if( i_mask & ATTRIBUTE_X )
        p_region->i_x = i_x;
    else if( i_mask & ATTRIBUTE_X_PERCENT )
        p_region->i_x = 0;

    if( i_mask & ATTRIBUTE_Y )
        p_region->i_y = i_y;
    else if( i_mask & ATTRIBUTE_Y_PERCENT )
        p_region->i_y = 0;
}