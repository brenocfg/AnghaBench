#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct input_manager {TYPE_2__* video_buffer; int /*<<< orphan*/  screen; struct controller* controller; } ;
struct fps_counter {int dummy; } ;
struct controller {int dummy; } ;
struct control_msg {int dummy; } ;
struct TYPE_6__ {int mod; int sym; } ;
struct TYPE_8__ {scalar_t__ type; int repeat; TYPE_1__ keysym; } ;
struct TYPE_7__ {struct fps_counter* fps_counter; } ;
typedef  int SDL_Keycode ;
typedef  TYPE_3__ SDL_KeyboardEvent ;

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
 int /*<<< orphan*/  SCREEN_POWER_MODE_OFF ; 
#define  SDLK_BACKSPACE 143 
#define  SDLK_DOWN 142 
#define  SDLK_UP 141 
#define  SDLK_b 140 
#define  SDLK_c 139 
#define  SDLK_f 138 
#define  SDLK_g 137 
#define  SDLK_h 136 
#define  SDLK_i 135 
#define  SDLK_m 134 
#define  SDLK_n 133 
#define  SDLK_o 132 
#define  SDLK_p 131 
#define  SDLK_s 130 
#define  SDLK_v 129 
#define  SDLK_x 128 
 scalar_t__ SDL_KEYDOWN ; 
 int /*<<< orphan*/  action_app_switch (struct controller*,int) ; 
 int /*<<< orphan*/  action_back (struct controller*,int) ; 
 int /*<<< orphan*/  action_home (struct controller*,int) ; 
 int /*<<< orphan*/  action_menu (struct controller*,int) ; 
 int /*<<< orphan*/  action_power (struct controller*,int) ; 
 int /*<<< orphan*/  action_volume_down (struct controller*,int) ; 
 int /*<<< orphan*/  action_volume_up (struct controller*,int) ; 
 int /*<<< orphan*/  clipboard_paste (struct controller*) ; 
 int /*<<< orphan*/  collapse_notification_panel (struct controller*) ; 
 int /*<<< orphan*/  controller_push_msg (struct controller*,struct control_msg*) ; 
 scalar_t__ convert_input_key (TYPE_3__ const*,struct control_msg*) ; 
 int /*<<< orphan*/  expand_notification_panel (struct controller*) ; 
 int /*<<< orphan*/  request_device_clipboard (struct controller*) ; 
 int /*<<< orphan*/  screen_resize_to_fit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_resize_to_pixel_perfect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_switch_fullscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_device_clipboard (struct controller*) ; 
 int /*<<< orphan*/  set_screen_power_mode (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_fps_counter_state (struct fps_counter*) ; 

void
input_manager_process_key(struct input_manager *input_manager,
                          const SDL_KeyboardEvent *event,
                          bool control) {
    // control: indicates the state of the command-line option --no-control
    // ctrl: the Ctrl key

    bool ctrl = event->keysym.mod & (KMOD_LCTRL | KMOD_RCTRL);
    bool alt = event->keysym.mod & (KMOD_LALT | KMOD_RALT);
    bool meta = event->keysym.mod & (KMOD_LGUI | KMOD_RGUI);

    // use Cmd on macOS, Ctrl on other platforms
#ifdef __APPLE__
    bool cmd = !ctrl && meta;
#else
    if (meta) {
        // no shortcuts involve Meta on platforms other than macOS, and it must
        // not be forwarded to the device
        return;
    }
    bool cmd = ctrl; // && !meta, already guaranteed
#endif

    if (alt) {
        // no shortcuts involve Alt, and it must not be forwarded to the device
        return;
    }

    struct controller *controller = input_manager->controller;

    // capture all Ctrl events
    if (ctrl || cmd) {
        SDL_Keycode keycode = event->keysym.sym;
        bool down = event->type == SDL_KEYDOWN;
        int action = down ? ACTION_DOWN : ACTION_UP;
        bool repeat = event->repeat;
        bool shift = event->keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT);
        switch (keycode) {
            case SDLK_h:
                // Ctrl+h on all platform, since Cmd+h is already captured by
                // the system on macOS to hide the window
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_home(controller, action);
                }
                return;
            case SDLK_b: // fall-through
            case SDLK_BACKSPACE:
                if (control && cmd && !shift && !repeat) {
                    action_back(controller, action);
                }
                return;
            case SDLK_s:
                if (control && cmd && !shift && !repeat) {
                    action_app_switch(controller, action);
                }
                return;
            case SDLK_m:
                // Ctrl+m on all platform, since Cmd+m is already captured by
                // the system on macOS to minimize the window
                if (control && ctrl && !meta && !shift && !repeat) {
                    action_menu(controller, action);
                }
                return;
            case SDLK_p:
                if (control && cmd && !shift && !repeat) {
                    action_power(controller, action);
                }
                return;
            case SDLK_o:
                if (control && cmd && !shift && down) {
                    set_screen_power_mode(controller, SCREEN_POWER_MODE_OFF);
                }
                return;
            case SDLK_DOWN:
                if (control && cmd && !shift) {
                    // forward repeated events
                    action_volume_down(controller, action);
                }
                return;
            case SDLK_UP:
                if (control && cmd && !shift) {
                    // forward repeated events
                    action_volume_up(controller, action);
                }
                return;
            case SDLK_c:
                if (control && cmd && !shift && !repeat && down) {
                    request_device_clipboard(controller);
                }
                return;
            case SDLK_v:
                if (control && cmd && !repeat && down) {
                    if (shift) {
                        // store the text in the device clipboard
                        set_device_clipboard(controller);
                    } else {
                        // inject the text as input events
                        clipboard_paste(controller);
                    }
                }
                return;
            case SDLK_f:
                if (!shift && cmd && !repeat && down) {
                    screen_switch_fullscreen(input_manager->screen);
                }
                return;
            case SDLK_x:
                if (!shift && cmd && !repeat && down) {
                    screen_resize_to_fit(input_manager->screen);
                }
                return;
            case SDLK_g:
                if (!shift && cmd && !repeat && down) {
                    screen_resize_to_pixel_perfect(input_manager->screen);
                }
                return;
            case SDLK_i:
                if (!shift && cmd && !repeat && down) {
                    struct fps_counter *fps_counter =
                        input_manager->video_buffer->fps_counter;
                    switch_fps_counter_state(fps_counter);
                }
                return;
            case SDLK_n:
                if (control && cmd && !repeat && down) {
                    if (shift) {
                        collapse_notification_panel(controller);
                    } else {
                        expand_notification_panel(controller);
                    }
                }
                return;
        }

        return;
    }

    if (!control) {
        return;
    }

    struct control_msg msg;
    if (convert_input_key(event, &msg)) {
        if (!controller_push_msg(controller, &msg)) {
            LOGW("Could not request 'inject keycode'");
        }
    }
}