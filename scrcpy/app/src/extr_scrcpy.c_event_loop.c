#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum event_result { ____Placeholder_event_result } event_result ;
typedef  int /*<<< orphan*/  SDL_Event ;

/* Variables and functions */
#define  EVENT_RESULT_CONTINUE 130 
#define  EVENT_RESULT_STOPPED_BY_EOS 129 
#define  EVENT_RESULT_STOPPED_BY_USER 128 
 int /*<<< orphan*/  SDL_AddEventWatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_WaitEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_watcher ; 
 int handle_event (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
event_loop(bool display, bool control) {
#ifdef CONTINUOUS_RESIZING_WORKAROUND
    if (display) {
        SDL_AddEventWatch(event_watcher, NULL);
    }
#endif
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        enum event_result result = handle_event(&event, control);
        switch (result) {
            case EVENT_RESULT_STOPPED_BY_USER:
                return true;
            case EVENT_RESULT_STOPPED_BY_EOS:
                return false;
            case EVENT_RESULT_CONTINUE:
                break;
        }
    }
    return false;
}