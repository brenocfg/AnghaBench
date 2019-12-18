#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  psz_module; } ;
typedef  TYPE_2__ vlc_log_t ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ intf_thread_t ;
struct TYPE_10__ {int i_msgs; scalar_t__ color; int /*<<< orphan*/  msg_lock; TYPE_1__* msgs; } ;
typedef  TYPE_4__ intf_sys_t ;
struct TYPE_7__ {int /*<<< orphan*/  msg; scalar_t__ type; TYPE_2__* item; } ;

/* Variables and functions */
 scalar_t__ C_DEFAULT ; 
 scalar_t__ C_INFO ; 
 int /*<<< orphan*/  MainBoxWrite (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_set (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DrawMessages(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;
    int l = 0;

    vlc_mutex_lock(&sys->msg_lock);
    int i = sys->i_msgs;
    for(;;) {
        vlc_log_t *msg = sys->msgs[i].item;
        if (msg) {
            if (sys->color)
                color_set(sys->msgs[i].type + C_INFO, NULL);
            MainBoxWrite(sys, l++, "[%s] %s", msg->psz_module, sys->msgs[i].msg);
        }

        if (++i == sizeof sys->msgs / sizeof *sys->msgs)
            i = 0;

        if (i == sys->i_msgs) /* did we loop around the ring buffer ? */
            break;
    }

    vlc_mutex_unlock(&sys->msg_lock);
    if (sys->color)
        color_set(C_DEFAULT, NULL);

    return l;
}