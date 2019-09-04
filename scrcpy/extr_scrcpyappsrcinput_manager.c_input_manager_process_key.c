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
struct input_manager {int /*<<< orphan*/  controller; int /*<<< orphan*/  video_buffer; int /*<<< orphan*/  screen; } ;
struct control_event {int dummy; } ;
struct TYPE_5__ {int mod; int sym; } ;
struct TYPE_6__ {scalar_t__ type; int repeat; TYPE_1__ keysym; } ;
typedef  int SDL_Keycode ;
typedef  TYPE_2__ SDL_KeyboardEvent ;

/* Variables and functions */
 int ACTION_DOWN ; 
 int ACTION_UP ; 
 int KMOD_LALT ; 
 int KMOD_LCTRL ; 
 int KMOD_LGUI ; 
 int KMOD_LSHIFT ; 
 int KMOD_RALT ; 
 int KMOD_RCTRL ; 
 int KMOD_RGUI ; 
 int KMOD_RSHIFT ; 
 int /*<<< orphan*/  LOGW (char*) ; 
#define  SDLK_BACKSPACE 141 
#define  SDLK_DOWN 140 
#define  SDLK_UP 139 
#define  SDLK_b 138 
#define  SDLK_f 137 
#define  SDLK_g 136 
#define  SDLK_h 135 
#define  SDLK_i 134 
#define  SDLK_m 133 
#define  SDLK_n 132 
#define  SDLK_p 131 
#define  SDLK_s 130 
#define  SDLK_v 129 
#define  SDLK_x 128 
 scalar_t__ SDL_KEYDOWN ; 
 int /*<<< orphan*/  action_app_switch (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_back (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_home (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_menu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_power (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_volume_down (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  action_volume_up (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clipboard_paste (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collapse_notification_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  controller_push_event (int /*<<< orphan*/ ,struct control_event*) ; 
 int /*<<< orphan*/  expand_notification_panel (int /*<<< orphan*/ ) ; 
 scalar_t__ input_key_from_sdl_to_android (TYPE_2__ const*,struct control_event*) ; 
 int /*<<< orphan*/  screen_resize_to_fit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_resize_to_pixel_perfect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_switch_fullscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_fps_counter_state (int /*<<< orphan*/ ) ; 

void
input_manager_process_key(struct input_manager *input_manager,
                          const SDL_KeyboardEvent *event,
                          bool control) {
    bool ctrl = event->keysym.mod & (KMOD_LCTRL | KMOD_RCTRL);
    bool alt = event->keysym.mod & (KMOD_LALT | KMOD_RALT);
    bool meta = event->keysym.mod & (KMOD_LGUI | KMOD_RGUI);

    if (alt) {
        // no shortcut involves Alt or Meta, and they should not be forwarded
        // to the device
        return;
    }

    // capture all Ctrl events
    if (ctrl | meta) {
        SDL_Keycode keycode = event->keysym.sym;
        int action = event->type == SDL_KEYDOWN ? ACTION_DOWN : ACTION_UP;
        bool repeat = event->repeat;
        bool shift = event->keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT);
        switch (keycode) {
            case SDLK_h:
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_home(input_manager->controller, action);
                }
                return;
            case SDLK_b: // fall-through
            case SDLK_BACKSPACE:
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_back(input_manager->controller, action);
                }
                return;
            case SDLK_s:
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_app_switch(input_manager->controller, action);
                }
                return;
            case SDLK_m:
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_menu(input_manager->controller, action);
                }
                return;
            case SDLK_p:
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_power(input_manager->controller, action);
                }
                return;
            case SDLK_DOWN:
#ifdef __APPLE__
                if (control && !ctrl && meta && !shift) {
#else
                if (control && ctrl && !meta && !shift) {
#endif
                    // forward repeated events
                    action_volume_down(input_manager->controller, action);
                }
                return;
            case SDLK_UP:
#ifdef __APPLE__
                if (control && !ctrl && meta && !shift) {
#else
                if (control && ctrl && !meta && !shift) {
#endif
                    // forward repeated events
                    action_volume_up(input_manager->controller, action);
                }
                return;
            case SDLK_v:
                if (control && ctrl && !meta && !shift && !repeat
                        && event->type == SDL_KEYDOWN) {
                    clipboard_paste(input_manager->controller);
                }
                return;
            case SDLK_f:
                if (ctrl && !meta && !shift && !repeat
                        && event->type == SDL_KEYDOWN) {
                    screen_switch_fullscreen(input_manager->screen);
                }
                return;
            case SDLK_x:
                if (ctrl && !meta && !shift && !repeat
                        && event->type == SDL_KEYDOWN) {
                    screen_resize_to_fit(input_manager->screen);
                }
                return;
            case SDLK_g:
                if (ctrl && !meta && !shift && !repeat
                        && event->type == SDL_KEYDOWN) {
                    screen_resize_to_pixel_perfect(input_manager->screen);
                }
                return;
            case SDLK_i:
                if (ctrl && !meta && !shift && !repeat
                        && event->type == SDL_KEYDOWN) {
                    switch_fps_counter_state(input_manager->video_buffer);
                }
                return;
            case SDLK_n:
                if (control && ctrl && !meta
                        && !repeat && event->type == SDL_KEYDOWN) {
                    if (shift) {
                        collapse_notification_panel(input_manager->controller);
                    } else {
                        expand_notification_panel(input_manager->controller);
                    }
                }
                return;
        }

        return;
    }

    if (!control) {
        return;
    }

    struct control_event control_event;
    if (input_key_from_sdl_to_android(event, &control_event)) {
        if (!controller_push_event(input_manager->controller, &control_event)) {
            LOGW("Cannot send control event");
        }
    }
}