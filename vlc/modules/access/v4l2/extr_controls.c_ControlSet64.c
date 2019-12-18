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
struct TYPE_3__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ vlc_v4l2_ctrl_t ;
struct v4l2_ext_controls {int count; struct v4l2_ext_control* controls; int /*<<< orphan*/  error_idx; int /*<<< orphan*/  ctrl_class; } ;
struct v4l2_ext_control {int /*<<< orphan*/  value64; int /*<<< orphan*/  size; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CTRL_ID2CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDIOC_S_EXT_CTRLS ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_ext_controls*) ; 

__attribute__((used)) static int ControlSet64 (const vlc_v4l2_ctrl_t *c, int64_t value)
{
    struct v4l2_ext_control ext_ctrl = {
        .id = c->id,
        .size = 0,
    };
    ext_ctrl.value64 = value;
    struct v4l2_ext_controls ext_ctrls = {
        .ctrl_class = V4L2_CTRL_ID2CLASS(c->id),
        .count = 1,
        .error_idx = 0,
        .controls = &ext_ctrl,
    };

    if (v4l2_ioctl (c->fd, VIDIOC_S_EXT_CTRLS, &ext_ctrls) < 0)
        return -1;
    return 0;
}