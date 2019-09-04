#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct input_manager {int /*<<< orphan*/  controller; TYPE_1__* screen; } ;
struct control_event {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  frame_size; } ;
typedef  TYPE_2__ SDL_MouseMotionEvent ;

/* Variables and functions */
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  controller_push_event (int /*<<< orphan*/ ,struct control_event*) ; 
 scalar_t__ mouse_motion_from_sdl_to_android (TYPE_2__ const*,int /*<<< orphan*/ ,struct control_event*) ; 

void
input_manager_process_mouse_motion(struct input_manager *input_manager,
                                   const SDL_MouseMotionEvent *event) {
    if (!event->state) {
        // do not send motion events when no button is pressed
        return;
    }
    struct control_event control_event;
    if (mouse_motion_from_sdl_to_android(event,
                                         input_manager->screen->frame_size,
                                         &control_event)) {
        if (!controller_push_event(input_manager->controller, &control_event)) {
            LOGW("Cannot send mouse motion event");
        }
    }
}