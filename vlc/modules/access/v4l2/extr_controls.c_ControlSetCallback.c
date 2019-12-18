#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  psz_string; int /*<<< orphan*/  i_int; int /*<<< orphan*/  b_bool; } ;
typedef  TYPE_1__ vlc_value_t ;
struct TYPE_9__ {int type; } ;
typedef  TYPE_2__ vlc_v4l2_ctrl_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int ControlSet (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int ControlSet64 (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int ControlSetStr (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
#define  V4L2_CTRL_TYPE_BITMASK 135 
#define  V4L2_CTRL_TYPE_BOOLEAN 134 
#define  V4L2_CTRL_TYPE_BUTTON 133 
#define  V4L2_CTRL_TYPE_INTEGER 132 
#define  V4L2_CTRL_TYPE_INTEGER64 131 
#define  V4L2_CTRL_TYPE_INTEGER_MENU 130 
#define  V4L2_CTRL_TYPE_MENU 129 
#define  V4L2_CTRL_TYPE_STRING 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ControlSetCallback (vlc_object_t *obj, const char *var,
                               vlc_value_t old, vlc_value_t cur, void *data)
{
    const vlc_v4l2_ctrl_t *ctrl = data;
    int ret;

    switch (ctrl->type)
    {
        case V4L2_CTRL_TYPE_INTEGER:
        case V4L2_CTRL_TYPE_MENU:
        case V4L2_CTRL_TYPE_BITMASK:
        case V4L2_CTRL_TYPE_INTEGER_MENU:
            ret = ControlSet (ctrl, cur.i_int);
            break;
        case V4L2_CTRL_TYPE_BOOLEAN:
            ret = ControlSet (ctrl, cur.b_bool);
            break;
        case V4L2_CTRL_TYPE_BUTTON:
            ret = ControlSet (ctrl, 0);
            break;
        case V4L2_CTRL_TYPE_INTEGER64:
            ret = ControlSet64 (ctrl, cur.i_int);
            break;
        case V4L2_CTRL_TYPE_STRING:
            ret = ControlSetStr (ctrl, cur.psz_string);
            break;
        default:
            vlc_assert_unreachable ();
    }

    if (ret)
    {
        msg_Err (obj, "cannot set control %s: %s", var, vlc_strerror_c(errno));
        return VLC_EGENERIC;
    }
    (void) old;
    return VLC_SUCCESS;
}