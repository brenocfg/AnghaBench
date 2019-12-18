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
struct controller {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; scalar_t__ stopped; int /*<<< orphan*/  msg_cond; } ;
struct control_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 scalar_t__ cbuf_is_empty (int /*<<< orphan*/ *) ; 
 int cbuf_take (int /*<<< orphan*/ *,struct control_msg*) ; 
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_msg_destroy (struct control_msg*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int process_msg (struct controller*,struct control_msg*) ; 

__attribute__((used)) static int
run_controller(void *data) {
    struct controller *controller = data;

    for (;;) {
        mutex_lock(controller->mutex);
        while (!controller->stopped && cbuf_is_empty(&controller->queue)) {
            cond_wait(controller->msg_cond, controller->mutex);
        }
        if (controller->stopped) {
            // stop immediately, do not process further msgs
            mutex_unlock(controller->mutex);
            break;
        }
        struct control_msg msg;
        bool non_empty = cbuf_take(&controller->queue, &msg);
        SDL_assert(non_empty);
        mutex_unlock(controller->mutex);

        bool ok = process_msg(controller, &msg);
        control_msg_destroy(&msg);
        if (!ok) {
            LOGD("Could not write msg to socket");
            break;
        }
    }
    return 0;
}