#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int video_transform_t ;

/* Variables and functions */
 int ORIENT_IS_MIRROR (int) ; 
#define  TRANSFORM_ANTI_TRANSPOSE 135 
#define  TRANSFORM_HFLIP 134 
#define  TRANSFORM_IDENTITY 133 
#define  TRANSFORM_R180 132 
#define  TRANSFORM_R270 131 
#define  TRANSFORM_R90 130 
#define  TRANSFORM_TRANSPOSE 129 
#define  TRANSFORM_VFLIP 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void transform_GetBasicOps( video_transform_t transform,
                                   unsigned *restrict angle,
                                   bool *restrict hflip )
{
    *hflip = ORIENT_IS_MIRROR(transform);

    switch ( transform )
    {
        case TRANSFORM_R90:
        case TRANSFORM_TRANSPOSE:
            *angle = 90;
            break;
        case TRANSFORM_R180:
        case TRANSFORM_VFLIP:
            *angle = 180;
            break;
        case TRANSFORM_R270:
        case TRANSFORM_ANTI_TRANSPOSE:
            *angle = 270;
            break;
        case TRANSFORM_HFLIP:
        case TRANSFORM_IDENTITY:
            *angle = 0;
            break;
        default:
            vlc_assert_unreachable ();
    }
}