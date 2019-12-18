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
struct controller {int /*<<< orphan*/  receiver; int /*<<< orphan*/  queue; int /*<<< orphan*/  mutex; int /*<<< orphan*/  msg_cond; } ;
struct control_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 scalar_t__ cbuf_take (int /*<<< orphan*/ *,struct control_msg*) ; 
 int /*<<< orphan*/  control_msg_destroy (struct control_msg*) ; 
 int /*<<< orphan*/  receiver_destroy (int /*<<< orphan*/ *) ; 

void
controller_destroy(struct controller *controller) {
    SDL_DestroyCond(controller->msg_cond);
    SDL_DestroyMutex(controller->mutex);

    struct control_msg msg;
    while (cbuf_take(&controller->queue, &msg)) {
        control_msg_destroy(&msg);
    }

    receiver_destroy(&controller->receiver);
}