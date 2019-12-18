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
struct controller {int dummy; } ;
struct TYPE_2__ {char* text; } ;
struct control_msg {TYPE_1__ set_clipboard; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_MSG_TYPE_SET_CLIPBOARD ; 
 int /*<<< orphan*/  LOGW (char*,...) ; 
 char* SDL_GetClipboardText () ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_free (char*) ; 
 int /*<<< orphan*/  controller_push_msg (struct controller*,struct control_msg*) ; 

__attribute__((used)) static void
set_device_clipboard(struct controller *controller) {
    char *text = SDL_GetClipboardText();
    if (!text) {
        LOGW("Could not get clipboard text: %s", SDL_GetError());
        return;
    }
    if (!*text) {
        // empty text
        SDL_free(text);
        return;
    }

    struct control_msg msg;
    msg.type = CONTROL_MSG_TYPE_SET_CLIPBOARD;
    msg.set_clipboard.text = text;

    if (!controller_push_msg(controller, &msg)) {
        SDL_free(text);
        LOGW("Could not request 'set device clipboard'");
    }
}