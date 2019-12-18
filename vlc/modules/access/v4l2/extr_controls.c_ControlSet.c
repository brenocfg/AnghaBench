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
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_S_CTRL ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_control*) ; 

__attribute__((used)) static int ControlSet (const vlc_v4l2_ctrl_t *c, int_fast32_t value)
{
    struct v4l2_control ctrl = {
        .id = c->id,
        .value = value,
    };
    if (v4l2_ioctl (c->fd, VIDIOC_S_CTRL, &ctrl) < 0)
        return -1;
    return 0;
}