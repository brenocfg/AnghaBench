#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int numerator; unsigned int denominator; } ;
struct v4l2_cropcap {TYPE_1__ pixelaspect; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_CROPCAP ; 
 scalar_t__ v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_cropcap*) ; 

__attribute__((used)) static void GetAR (int fd, unsigned *restrict num, unsigned *restrict den)
{
    struct v4l2_cropcap cropcap = { .type = V4L2_BUF_TYPE_VIDEO_CAPTURE };

    /* TODO: get CROPCAP only once (see ResetCrop()). */
    if (v4l2_ioctl (fd, VIDIOC_CROPCAP, &cropcap) < 0)
    {
        *num = *den = 1;
        return;
    }
    *num = cropcap.pixelaspect.numerator;
    *den = cropcap.pixelaspect.denominator;
}