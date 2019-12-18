#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_handler_action_t ;
typedef  enum event_result { ____Placeholder_event_result } event_result ;
struct TYPE_12__ {int has_frame; } ;
struct TYPE_10__ {int /*<<< orphan*/  file; } ;
struct TYPE_9__ {int /*<<< orphan*/  event; } ;
struct TYPE_11__ {int type; TYPE_2__ drop; int /*<<< orphan*/  button; int /*<<< orphan*/  wheel; int /*<<< orphan*/  motion; int /*<<< orphan*/  key; int /*<<< orphan*/  text; TYPE_1__ window; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_INSTALL_APK ; 
 int /*<<< orphan*/  ACTION_PUSH_FILE ; 
#define  EVENT_NEW_FRAME 141 
 int EVENT_RESULT_CONTINUE ; 
 int EVENT_RESULT_STOPPED_BY_EOS ; 
 int EVENT_RESULT_STOPPED_BY_USER ; 
#define  EVENT_STREAM_STOPPED 140 
 int /*<<< orphan*/  LOGD (char*) ; 
#define  SDL_DROPFILE 139 
#define  SDL_KEYDOWN 138 
#define  SDL_KEYUP 137 
#define  SDL_MOUSEBUTTONDOWN 136 
#define  SDL_MOUSEBUTTONUP 135 
#define  SDL_MOUSEMOTION 134 
#define  SDL_MOUSEWHEEL 133 
#define  SDL_QUIT 132 
#define  SDL_TEXTINPUT 131 
#define  SDL_WINDOWEVENT 130 
#define  SDL_WINDOWEVENT_EXPOSED 129 
#define  SDL_WINDOWEVENT_SIZE_CHANGED 128 
 int /*<<< orphan*/  file_handler ; 
 int /*<<< orphan*/  file_handler_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_manager ; 
 int /*<<< orphan*/  input_manager_process_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  input_manager_process_mouse_button (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  input_manager_process_mouse_motion (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_manager_process_mouse_wheel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_manager_process_text_input (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_apk (int /*<<< orphan*/ ) ; 
 TYPE_4__ screen ; 
 int /*<<< orphan*/  screen_render (TYPE_4__*) ; 
 int /*<<< orphan*/  screen_show_window (TYPE_4__*) ; 
 int /*<<< orphan*/  screen_update_frame (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_buffer ; 

__attribute__((used)) static enum event_result
handle_event(SDL_Event *event, bool control) {
    switch (event->type) {
        case EVENT_STREAM_STOPPED:
            LOGD("Video stream stopped");
            return EVENT_RESULT_STOPPED_BY_EOS;
        case SDL_QUIT:
            LOGD("User requested to quit");
            return EVENT_RESULT_STOPPED_BY_USER;
        case EVENT_NEW_FRAME:
            if (!screen.has_frame) {
                screen.has_frame = true;
                // this is the very first frame, show the window
                screen_show_window(&screen);
            }
            if (!screen_update_frame(&screen, &video_buffer)) {
                return EVENT_RESULT_CONTINUE;
            }
            break;
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
                case SDL_WINDOWEVENT_EXPOSED:
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    screen_render(&screen);
                    break;
            }
            break;
        case SDL_TEXTINPUT:
            if (!control) {
                break;
            }
            input_manager_process_text_input(&input_manager, &event->text);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            // some key events do not interact with the device, so process the
            // event even if control is disabled
            input_manager_process_key(&input_manager, &event->key, control);
            break;
        case SDL_MOUSEMOTION:
            if (!control) {
                break;
            }
            input_manager_process_mouse_motion(&input_manager, &event->motion);
            break;
        case SDL_MOUSEWHEEL:
            if (!control) {
                break;
            }
            input_manager_process_mouse_wheel(&input_manager, &event->wheel);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            // some mouse events do not interact with the device, so process
            // the event even if control is disabled
            input_manager_process_mouse_button(&input_manager, &event->button,
                                               control);
            break;
        case SDL_DROPFILE: {
            if (!control) {
                break;
            }
            file_handler_action_t action;
            if (is_apk(event->drop.file)) {
                action = ACTION_INSTALL_APK;
            } else {
                action = ACTION_PUSH_FILE;
            }
            file_handler_request(&file_handler, action, event->drop.file);
            break;
        }
    }
    return EVENT_RESULT_CONTINUE;
}