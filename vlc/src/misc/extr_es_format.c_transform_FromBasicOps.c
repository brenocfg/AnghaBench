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
typedef  int /*<<< orphan*/  video_transform_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSFORM_ANTI_TRANSPOSE ; 
 int /*<<< orphan*/  TRANSFORM_HFLIP ; 
 int /*<<< orphan*/  TRANSFORM_IDENTITY ; 
 int /*<<< orphan*/  TRANSFORM_R180 ; 
 int /*<<< orphan*/  TRANSFORM_R270 ; 
 int /*<<< orphan*/  TRANSFORM_R90 ; 
 int /*<<< orphan*/  TRANSFORM_TRANSPOSE ; 
 int /*<<< orphan*/  TRANSFORM_VFLIP ; 

__attribute__((used)) static video_transform_t transform_FromBasicOps( unsigned angle, bool hflip )
{
    switch ( angle )
    {
        case 90:
            return hflip ? TRANSFORM_TRANSPOSE : TRANSFORM_R90;
        case 180:
            return hflip ? TRANSFORM_VFLIP : TRANSFORM_R180;
        case 270:
            return hflip ? TRANSFORM_ANTI_TRANSPOSE : TRANSFORM_R270;
        default:
            return hflip ? TRANSFORM_HFLIP : TRANSFORM_IDENTITY;
    }
}