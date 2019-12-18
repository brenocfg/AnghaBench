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
typedef  int /*<<< orphan*/  video_transform_t ;
typedef  scalar_t__ video_orientation_t ;
struct TYPE_3__ {scalar_t__ orientation; int /*<<< orphan*/  i_sar_num; int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_x_offset; int /*<<< orphan*/  i_y_offset; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_height; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 scalar_t__ ORIENT_ANTI_TRANSPOSED ; 
 scalar_t__ ORIENT_HFLIPPED ; 
 scalar_t__ ORIENT_IS_SWAP (scalar_t__) ; 
 scalar_t__ ORIENT_NORMAL ; 
 scalar_t__ ORIENT_ROTATED_180 ; 
 scalar_t__ ORIENT_ROTATED_270 ; 
 scalar_t__ ORIENT_ROTATED_90 ; 
 scalar_t__ ORIENT_TRANSPOSED ; 
 scalar_t__ ORIENT_VFLIPPED ; 
 int /*<<< orphan*/  transform_GetBasicOps (int /*<<< orphan*/ ,unsigned int*,int*) ; 

void video_format_TransformBy( video_format_t *fmt, video_transform_t transform )
{
    /* Get destination orientation */
    unsigned angle1, angle2;
    bool hflip1, hflip2;

    transform_GetBasicOps( transform, &angle1, &hflip1 );
    transform_GetBasicOps( (video_transform_t)fmt->orientation, &angle2, &hflip2 );

    unsigned angle = (angle2 - angle1 + 360) % 360;
    bool hflip = hflip2 ^ hflip1;

    video_orientation_t dst_orient = ORIENT_NORMAL;

    if( hflip ) {

        if( angle == 0 )
            dst_orient = ORIENT_HFLIPPED;
        else if( angle == 90 )
            dst_orient = ORIENT_ANTI_TRANSPOSED;
        else if( angle == 180 )
            dst_orient = ORIENT_VFLIPPED;
        else if( angle == 270 )
            dst_orient = ORIENT_TRANSPOSED;
    }
    else {

        if( angle == 90 )
            dst_orient = ORIENT_ROTATED_90;
        else if( angle == 180 )
            dst_orient = ORIENT_ROTATED_180;
        else if( angle == 270 )
            dst_orient = ORIENT_ROTATED_270;
    }

    /* Apply transform */
    if( ORIENT_IS_SWAP( fmt->orientation ) != ORIENT_IS_SWAP( dst_orient ) )
    {
        video_format_t scratch = *fmt;

        fmt->i_width = scratch.i_height;
        fmt->i_visible_width = scratch.i_visible_height;
        fmt->i_height = scratch.i_width;
        fmt->i_visible_height = scratch.i_visible_width;
        fmt->i_x_offset = scratch.i_y_offset;
        fmt->i_y_offset = scratch.i_x_offset;
        fmt->i_sar_num = scratch.i_sar_den;
        fmt->i_sar_den = scratch.i_sar_num;
    }

    fmt->orientation = dst_orient;
}