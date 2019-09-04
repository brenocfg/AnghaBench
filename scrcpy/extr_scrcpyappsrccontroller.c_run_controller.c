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
struct controller {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; scalar_t__ stopped; int /*<<< orphan*/  event_cond; } ;
struct control_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_event_destroy (struct control_event*) ; 
 scalar_t__ control_event_queue_is_empty (int /*<<< orphan*/ *) ; 
 int control_event_queue_take (int /*<<< orphan*/ *,struct control_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int process_event (struct controller*,struct control_event*) ; 

__attribute__((used)) static int
run_controller(void *data) {
    struct controller *controller = data;

    for (;;) {
        mutex_lock(controller->mutex);
        while (!controller->stopped
                && control_event_queue_is_empty(&controller->queue)) {
            cond_wait(controller->event_cond, controller->mutex);
        }
        if (controller->stopped) {
            // stop immediately, do not process further events
            mutex_unlock(controller->mutex);
            break;
        }
        struct control_event event;
        bool non_empty = control_event_queue_take(&controller->queue,
                                                      &event);
        SDL_assert(non_empty);
        mutex_unlock(controller->mutex);

        bool ok = process_event(controller, &event);
        control_event_destroy(&event);
        if (!ok) {
            LOGD("Cannot write event to socket");
            break;
        }
    }
    return 0;
}