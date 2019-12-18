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
struct screen {int /*<<< orphan*/  renderer; int /*<<< orphan*/  texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ ) ; 

void
screen_render(struct screen *screen) {
    SDL_RenderClear(screen->renderer);
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
    SDL_RenderPresent(screen->renderer);
}