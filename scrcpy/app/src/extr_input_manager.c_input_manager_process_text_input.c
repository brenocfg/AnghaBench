#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct input_manager {int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {int /*<<< orphan*/  text; } ;
struct control_msg {TYPE_1__ inject_text; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {char* text; } ;
typedef  TYPE_2__ SDL_TextInputEvent ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_MSG_TYPE_INJECT_TEXT ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_strdup (char*) ; 
 int /*<<< orphan*/  controller_push_msg (int /*<<< orphan*/ ,struct control_msg*) ; 
 scalar_t__ isalpha (char) ; 

void
input_manager_process_text_input(struct input_manager *input_manager,
                                 const SDL_TextInputEvent *event) {
    char c = event->text[0];
    if (isalpha(c) || c == ' ') {
        SDL_assert(event->text[1] == '\0');
        // letters and space are handled as raw key event
        return;
    }
    struct control_msg msg;
    msg.type = CONTROL_MSG_TYPE_INJECT_TEXT;
    msg.inject_text.text = SDL_strdup(event->text);
    if (!msg.inject_text.text) {
        LOGW("Could not strdup input text");
        return;
    }
    if (!controller_push_msg(input_manager->controller, &msg)) {
        SDL_free(msg.inject_text.text);
        LOGW("Could not request 'inject text'");
    }
}