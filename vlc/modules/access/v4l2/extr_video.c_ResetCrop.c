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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct v4l2_cropcap {int /*<<< orphan*/  c; int /*<<< orphan*/  defrect; int /*<<< orphan*/  type; } ;
struct v4l2_crop {int /*<<< orphan*/  c; int /*<<< orphan*/  defrect; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_CROPCAP ; 
 int /*<<< orphan*/  VIDIOC_S_CROP ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_cropcap*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ResetCrop (vlc_object_t *obj, int fd)
{
    struct v4l2_cropcap cropcap = { .type = V4L2_BUF_TYPE_VIDEO_CAPTURE };

    /* In theory, this ioctl() must work for all video capture devices.
     * In practice, it does not. */
    if (v4l2_ioctl (fd, VIDIOC_CROPCAP, &cropcap) < 0)
    {
        msg_Dbg (obj, "cannot get cropping properties: %s",
                 vlc_strerror_c(errno));
        return 0;
    }

    /* Reset to the default cropping rectangle */
    struct v4l2_crop crop = {
        .type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
        .c = cropcap.defrect,
    };

    if (v4l2_ioctl (fd, VIDIOC_S_CROP, &crop) < 0)
    {
        msg_Warn (obj, "cannot reset cropping limits: %s",
                  vlc_strerror_c(errno));
        return -1;
    }
    return 0;
}