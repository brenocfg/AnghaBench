#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * p_address; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  char const vlc_object_t ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_10__ {int /*<<< orphan*/ * input; scalar_t__ is_master; int /*<<< orphan*/  thread; } ;
typedef  TYPE_3__ intf_sys_t ;
typedef  int /*<<< orphan*/  input_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  Master ; 
 int /*<<< orphan*/  Slave ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int PlaylistEvent(vlc_object_t *object, char const *cmd,
                         vlc_value_t oldval, vlc_value_t newval, void *data)
{
    VLC_UNUSED(cmd); VLC_UNUSED(object);
    intf_thread_t  *intf = data;
    intf_sys_t     *sys = intf->p_sys;
    input_thread_t *input = newval.p_address;

    if (sys->input != NULL) {
        msg_Err(intf, "InputEvent DEAD");
        assert(oldval.p_address == sys->input);

        vlc_cancel(sys->thread);
        vlc_join(sys->thread, NULL);
    }

    sys->input = input;

    if (input != NULL) {
        if (vlc_clone(&sys->thread, sys->is_master ? Master : Slave, intf,
                      VLC_THREAD_PRIORITY_INPUT))
            sys->input = NULL;
    }
    return VLC_SUCCESS;
}