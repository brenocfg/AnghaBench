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
struct control_msg {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  frame_size; } ;
typedef  TYPE_2__ SDL_MouseMotionEvent ;

/* Variables and functions */
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  controller_push_msg (int /*<<< orphan*/ ,struct control_msg*) ; 
 scalar_t__ convert_mouse_motion (TYPE_2__ const*,int /*<<< orphan*/ ,struct control_msg*) ; 

void
input_manager_process_mouse_motion(struct input_manager *input_manager,
                                   const SDL_MouseMotionEvent *event) {
    if (!event->state) {
        // do not send motion events when no button is pressed
        return;
    }
    struct control_msg msg;
    if (convert_mouse_motion(event, input_manager->screen->frame_size, &msg)) {
        if (!controller_push_msg(input_manager->controller, &msg)) {
            LOGW("Could not request 'inject mouse motion event'");
        }
    }
}