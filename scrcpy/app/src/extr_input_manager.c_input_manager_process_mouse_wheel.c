#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct position {int /*<<< orphan*/  point; int /*<<< orphan*/  screen_size; } ;
struct input_manager {int /*<<< orphan*/  controller; TYPE_1__* screen; } ;
struct control_msg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_size; } ;
typedef  int /*<<< orphan*/  SDL_MouseWheelEvent ;

/* Variables and functions */
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  controller_push_msg (int /*<<< orphan*/ ,struct control_msg*) ; 
 scalar_t__ convert_mouse_wheel (int /*<<< orphan*/  const*,struct position,struct control_msg*) ; 
 int /*<<< orphan*/  get_mouse_point (TYPE_1__*) ; 

void
input_manager_process_mouse_wheel(struct input_manager *input_manager,
                                  const SDL_MouseWheelEvent *event) {
    struct position position = {
        .screen_size = input_manager->screen->frame_size,
        .point = get_mouse_point(input_manager->screen),
    };
    struct control_msg msg;
    if (convert_mouse_wheel(event, position, &msg)) {
        if (!controller_push_msg(input_manager->controller, &msg)) {
            LOGW("Could not request 'inject mouse wheel event'");
        }
    }
}