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
struct receiver {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
receiver_join(struct receiver *receiver) {
    SDL_WaitThread(receiver->thread, NULL);
}