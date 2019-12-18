#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_2__* p; } ;
typedef  TYPE_3__ vout_thread_t ;
struct TYPE_25__ {int i_x; int i_y; scalar_t__ b_double_click; int /*<<< orphan*/  i_pressed; } ;
typedef  TYPE_4__ vlc_mouse_t ;
struct TYPE_22__ {int /*<<< orphan*/  lock; scalar_t__ chain_static; scalar_t__ chain_interactive; } ;
struct TYPE_23__ {int /*<<< orphan*/  mouse_opaque; int /*<<< orphan*/  (* mouse_event ) (TYPE_4__*,int /*<<< orphan*/ ) ;TYPE_4__ mouse; TYPE_1__ filter; int /*<<< orphan*/  display_lock; int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_BUTTON_LEFT ; 
 int /*<<< orphan*/  filter_chain_MouseFilter (scalar_t__,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_GetCoords (TYPE_3__*,char*,int*,int*) ; 
 int /*<<< orphan*/  var_SetCoords (TYPE_3__*,char*,int,int) ; 
 int /*<<< orphan*/  var_SetInteger (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_ToggleBool (TYPE_3__*,char*) ; 
 scalar_t__ vlc_mouse_HasButton (TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ vlc_mouse_HasMoved (TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ vlc_mouse_HasPressed (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_TranslateMouseState (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__ const*) ; 

__attribute__((used)) static void ThreadProcessMouseState(vout_thread_t *vout,
                                    const vlc_mouse_t *win_mouse)
{
    vlc_mouse_t vid_mouse, tmp1, tmp2, *m;

    /* Translate window coordinates to video coordinates */
    vlc_mutex_lock(&vout->p->display_lock);
    vout_display_TranslateMouseState(vout->p->display, &vid_mouse, win_mouse);
    vlc_mutex_unlock(&vout->p->display_lock);

    /* Then pass up the filter chains. */
    m = &vid_mouse;
    vlc_mutex_lock(&vout->p->filter.lock);
    if (vout->p->filter.chain_static && vout->p->filter.chain_interactive) {
        if (!filter_chain_MouseFilter(vout->p->filter.chain_interactive,
                                      &tmp1, m))
            m = &tmp1;
        if (!filter_chain_MouseFilter(vout->p->filter.chain_static,
                                      &tmp2, m))
            m = &tmp2;
    }
    vlc_mutex_unlock(&vout->p->filter.lock);

    if (vlc_mouse_HasMoved(&vout->p->mouse, m))
        var_SetCoords(vout, "mouse-moved", m->i_x, m->i_y);

    if (vlc_mouse_HasButton(&vout->p->mouse, m)) {
        var_SetInteger(vout, "mouse-button-down", m->i_pressed);

        if (vlc_mouse_HasPressed(&vout->p->mouse, m, MOUSE_BUTTON_LEFT)) {
            /* FIXME? */
            int x, y;

            var_GetCoords(vout, "mouse-moved", &x, &y);
            var_SetCoords(vout, "mouse-clicked", x, y);
        }
    }

    if (m->b_double_click)
        var_ToggleBool(vout, "fullscreen");
    vout->p->mouse = *m;

    if (vout->p->mouse_event)
        vout->p->mouse_event(m, vout->p->mouse_opaque);
}