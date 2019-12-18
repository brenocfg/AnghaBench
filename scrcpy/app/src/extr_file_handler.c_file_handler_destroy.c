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
struct file_handler_request {int dummy; } ;
struct file_handler {int /*<<< orphan*/  queue; int /*<<< orphan*/  serial; int /*<<< orphan*/  mutex; int /*<<< orphan*/  event_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 
 scalar_t__ cbuf_take (int /*<<< orphan*/ *,struct file_handler_request*) ; 
 int /*<<< orphan*/  file_handler_request_destroy (struct file_handler_request*) ; 

void
file_handler_destroy(struct file_handler *file_handler) {
    SDL_DestroyCond(file_handler->event_cond);
    SDL_DestroyMutex(file_handler->mutex);
    SDL_free(file_handler->serial);

    struct file_handler_request req;
    while (cbuf_take(&file_handler->queue, &req)) {
        file_handler_request_destroy(&req);
    }
}