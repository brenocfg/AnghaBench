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
struct control_event {TYPE_1__ text_event; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_EVENT_TYPE_TEXT ; 
 int /*<<< orphan*/  LOGW (char*,...) ; 
 char* SDL_GetClipboardText () ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_free (char*) ; 
 int /*<<< orphan*/  controller_push_event (struct controller*,struct control_event*) ; 

__attribute__((used)) static void
clipboard_paste(struct controller *controller) {
    char *text = SDL_GetClipboardText();
    if (!text) {
        LOGW("Cannot get clipboard text: %s", SDL_GetError());
        return;
    }
    if (!*text) {
        // empty text
        SDL_free(text);
        return;
    }

    struct control_event control_event;
    control_event.type = CONTROL_EVENT_TYPE_TEXT;
    control_event.text_event.text = text;
    if (!controller_push_event(controller, &control_event)) {
        SDL_free(text);
        LOGW("Cannot send clipboard paste event");
    }
}