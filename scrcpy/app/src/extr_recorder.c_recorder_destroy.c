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
struct recorder {int /*<<< orphan*/  filename; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 

void
recorder_destroy(struct recorder *recorder) {
    SDL_DestroyCond(recorder->queue_cond);
    SDL_DestroyMutex(recorder->mutex);
    SDL_free(recorder->filename);
}