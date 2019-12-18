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
typedef  int /*<<< orphan*/  video_transform_t ;
typedef  int /*<<< orphan*/  video_orientation_t ;
struct TYPE_4__ {int /*<<< orphan*/  orientation; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_format_GetTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_TransformBy (TYPE_1__*,int /*<<< orphan*/ ) ; 

void video_format_TransformTo( video_format_t *restrict fmt,
                               video_orientation_t dst_orientation )
{
    video_transform_t transform = video_format_GetTransform(fmt->orientation,
                                                            dst_orientation);
    video_format_TransformBy(fmt, transform);
}