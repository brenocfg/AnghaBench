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
typedef  int /*<<< orphan*/  vlc_v4l2_ctrl_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct v4l2_queryctrl {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_v4l2_ctrl_t *ControlAddClass (vlc_object_t *obj, int fd,
                                         const struct v4l2_queryctrl *query)
{
    msg_Dbg (obj, "control class %s:", query->name);
    (void) fd;
    return NULL;
}