#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_9__ {int i_int; } ;
typedef  TYPE_2__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ intf_thread_t ;
struct TYPE_8__ {int btn_pressed; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_11__ {TYPE_1__ vrnav; } ;
typedef  TYPE_4__ intf_sys_t ;

/* Variables and functions */
 int KEY_MOUSEWHEEL_FROM_BUTTON (int) ; 
 int MOUSE_BUTTON_CENTER ; 
 int MOUSE_BUTTON_LEFT ; 
 int MOUSE_BUTTON_RIGHT ; 
 int MOUSE_BUTTON_WHEEL_RIGHT ; 
 int MOUSE_BUTTON_WHEEL_UP ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 scalar_t__ var_GetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_GetCoords (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_3__*) ; 

__attribute__((used)) static int
MouseButtonCallback(vlc_object_t *obj, char const *var,
                    vlc_value_t oldval, vlc_value_t newval, void *data)
{
    VLC_UNUSED(var);

    intf_thread_t *intf = data;
    intf_sys_t *sys = intf->p_sys;
    vout_thread_t *vout = (vout_thread_t *)obj;

    if ((newval.i_int & (1 << MOUSE_BUTTON_LEFT)) &&
        var_GetBool(vout, "viewpoint-changeable"))
    {
        if (!sys->vrnav.btn_pressed)
        {
            sys->vrnav.btn_pressed = true;
            var_GetCoords(vout, "mouse-moved", &sys->vrnav.x, &sys->vrnav.y);
        }
    }
    else
        sys->vrnav.btn_pressed = false;

    unsigned pressed = newval.i_int & ~oldval.i_int;
    if (pressed & (1 << MOUSE_BUTTON_LEFT))
        var_SetBool(vlc_object_instance(intf), "intf-popupmenu", false);
    if (pressed & (1 << MOUSE_BUTTON_CENTER))
        var_TriggerCallback(vlc_object_instance(intf), "intf-toggle-fscontrol");
#ifndef _WIN32
    if (pressed & (1 << MOUSE_BUTTON_RIGHT))
#else
    if ((oldval.i_int & (1 << MOUSE_BUTTON_RIGHT))
     && !(newval.i_int & (1 << MOUSE_BUTTON_RIGHT)))
#endif
        var_SetBool(vlc_object_instance(intf), "intf-popupmenu", true);
    for (int i = MOUSE_BUTTON_WHEEL_UP; i <= MOUSE_BUTTON_WHEEL_RIGHT; i++)
        if (pressed & (1 << i))
        {
            int keycode = KEY_MOUSEWHEEL_FROM_BUTTON(i);
            var_SetInteger(vlc_object_instance(intf), "key-pressed", keycode);
        }

    return VLC_SUCCESS;
}