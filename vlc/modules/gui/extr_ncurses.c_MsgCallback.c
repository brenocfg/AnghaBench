#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_log_t ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {scalar_t__ verbosity; size_t i_msgs; int /*<<< orphan*/  msg_lock; TYPE_1__* msgs; } ;
typedef  TYPE_2__ intf_sys_t ;
struct TYPE_3__ {int type; char* msg; int /*<<< orphan*/ * item; } ;

/* Variables and functions */
 int VLC_MSG_ERR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * msg_Copy (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  msg_Free (int /*<<< orphan*/ *) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MsgCallback(void *data, int type, const vlc_log_t *msg,
                        const char *format, va_list ap)
{
    intf_sys_t *sys = data;
    char *text;

    if (sys->verbosity < 0
     || sys->verbosity < (type - VLC_MSG_ERR)
     || vasprintf(&text, format, ap) == -1)
        return;

    vlc_mutex_lock(&sys->msg_lock);

    sys->msgs[sys->i_msgs].type = type;
    if (sys->msgs[sys->i_msgs].item != NULL)
        msg_Free(sys->msgs[sys->i_msgs].item);
    sys->msgs[sys->i_msgs].item = msg_Copy(msg);
    free(sys->msgs[sys->i_msgs].msg);
    sys->msgs[sys->i_msgs].msg = text;

    if (++sys->i_msgs == (sizeof sys->msgs / sizeof *sys->msgs))
        sys->i_msgs = 0;

    vlc_mutex_unlock(&sys->msg_lock);
}