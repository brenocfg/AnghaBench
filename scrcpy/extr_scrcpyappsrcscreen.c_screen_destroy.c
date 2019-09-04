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
struct screen {scalar_t__ window; scalar_t__ renderer; scalar_t__ texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyRenderer (scalar_t__) ; 
 int /*<<< orphan*/  SDL_DestroyTexture (scalar_t__) ; 
 int /*<<< orphan*/  SDL_DestroyWindow (scalar_t__) ; 

void
screen_destroy(struct screen *screen) {
    if (screen->texture) {
        SDL_DestroyTexture(screen->texture);
    }
    if (screen->renderer) {
        SDL_DestroyRenderer(screen->renderer);
    }
    if (screen->window) {
        SDL_DestroyWindow(screen->window);
    }
}