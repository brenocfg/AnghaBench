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
struct input_manager {int /*<<< orphan*/  controller; TYPE_2__* screen; } ;
struct control_msg {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame_size; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ button; int clicks; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ SDL_MouseButtonEvent ;

/* Variables and functions */
 int ACTION_DOWN ; 
 int ACTION_UP ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 scalar_t__ SDL_BUTTON_LEFT ; 
 scalar_t__ SDL_BUTTON_MIDDLE ; 
 scalar_t__ SDL_BUTTON_RIGHT ; 
 scalar_t__ SDL_MOUSEBUTTONDOWN ; 
 int /*<<< orphan*/  action_home (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  controller_push_msg (int /*<<< orphan*/ ,struct control_msg*) ; 
 scalar_t__ convert_mouse_button (TYPE_1__ const*,int /*<<< orphan*/ ,struct control_msg*) ; 
 int is_outside_device_screen (struct input_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  press_back_or_turn_screen_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_resize_to_fit (TYPE_2__*) ; 

void
input_manager_process_mouse_button(struct input_manager *input_manager,
                                   const SDL_MouseButtonEvent *event,
                                   bool control) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (control && event->button == SDL_BUTTON_RIGHT) {
            press_back_or_turn_screen_on(input_manager->controller);
            return;
        }
        if (control && event->button == SDL_BUTTON_MIDDLE) {
            action_home(input_manager->controller, ACTION_DOWN | ACTION_UP);
            return;
        }
        // double-click on black borders resize to fit the device screen
        if (event->button == SDL_BUTTON_LEFT && event->clicks == 2) {
            bool outside =
                is_outside_device_screen(input_manager, event->x, event->y);
            if (outside) {
                screen_resize_to_fit(input_manager->screen);
                return;
            }
        }
        // otherwise, send the click event to the device
    }

    if (!control) {
        return;
    }

    struct control_msg msg;
    if (convert_mouse_button(event, input_manager->screen->frame_size, &msg)) {
        if (!controller_push_msg(input_manager->controller, &msg)) {
            LOGW("Could not request 'inject mouse button event'");
        }
    }
}