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
struct file_handler {scalar_t__ serial; int /*<<< orphan*/  queue; int /*<<< orphan*/  mutex; int /*<<< orphan*/  event_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_free (void*) ; 
 int /*<<< orphan*/  request_queue_destroy (int /*<<< orphan*/ *) ; 

void
file_handler_destroy(struct file_handler *file_handler) {
    SDL_DestroyCond(file_handler->event_cond);
    SDL_DestroyMutex(file_handler->mutex);
    request_queue_destroy(&file_handler->queue);
    SDL_free((void *) file_handler->serial);
}