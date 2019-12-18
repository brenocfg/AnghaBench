#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  has_double_click; } ;
struct TYPE_14__ {TYPE_5__* sys; } ;
struct TYPE_16__ {TYPE_2__ info; TYPE_1__ owner; } ;
typedef  TYPE_3__ vout_window_t ;
struct TYPE_17__ {int type; int /*<<< orphan*/  button_mask; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_4__ vout_window_mouse_event_t ;
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_19__ {int b_double_click; } ;
struct TYPE_18__ {void* last_left_press; TYPE_6__ mouse; int /*<<< orphan*/ * vout; } ;
typedef  TYPE_5__ vout_display_window_t ;
typedef  void* vlc_tick_t ;
typedef  TYPE_6__ vlc_mouse_t ;

/* Variables and functions */
 void* const DOUBLE_CLICK_TIME ; 
 void* INT64_MIN ; 
 int /*<<< orphan*/  MOUSE_BUTTON_LEFT ; 
#define  VOUT_WINDOW_MOUSE_DOUBLE_CLICK 131 
#define  VOUT_WINDOW_MOUSE_MOVED 130 
#define  VOUT_WINDOW_MOUSE_PRESSED 129 
#define  VOUT_WINDOW_MOUSE_RELEASED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_mouse_IsLeftPressed (TYPE_6__*) ; 
 int /*<<< orphan*/  vlc_mouse_SetPosition (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mouse_SetPressed (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mouse_SetReleased (TYPE_6__*,int /*<<< orphan*/ ) ; 
 void* vlc_tick_now () ; 
 int /*<<< orphan*/  vout_MouseState (int /*<<< orphan*/ *,TYPE_6__*) ; 

__attribute__((used)) static void vout_display_window_MouseEvent(vout_window_t *window,
                                           const vout_window_mouse_event_t *ev)
{
    vout_display_window_t *state = window->owner.sys;
    vout_thread_t *vout = state->vout;
    vlc_mouse_t *m = &state->mouse;

    m->b_double_click = false;

    switch (ev->type)
    {
        case VOUT_WINDOW_MOUSE_MOVED:
            vlc_mouse_SetPosition(m, ev->x, ev->y);
            state->last_left_press = INT64_MIN;
            break;

        case VOUT_WINDOW_MOUSE_PRESSED:
            if (!window->info.has_double_click
             && ev->button_mask == MOUSE_BUTTON_LEFT
             && !vlc_mouse_IsLeftPressed(m))
            {
                const vlc_tick_t now = vlc_tick_now();

                if (state->last_left_press != INT64_MIN
                 && now - state->last_left_press < DOUBLE_CLICK_TIME)
                {
                    m->b_double_click = true;
                    state->last_left_press = INT64_MIN;
                }
                else
                    state->last_left_press = now;
            }

            vlc_mouse_SetPressed(m, ev->button_mask);
            break;

        case VOUT_WINDOW_MOUSE_RELEASED:
            vlc_mouse_SetReleased(m, ev->button_mask);
            break;

        case VOUT_WINDOW_MOUSE_DOUBLE_CLICK:
            assert(window->info.has_double_click);
            m->b_double_click = true;
            break;

        default:
            vlc_assert_unreachable();
    }

    vout_MouseState(vout, m);
}