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
struct size {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct screen {int /*<<< orphan*/  window; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  fullscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  SDL_SetWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct size get_optimal_window_size (struct screen*,int /*<<< orphan*/ ) ; 

void
screen_resize_to_fit(struct screen *screen) {
    if (!screen->fullscreen) {
        struct size optimal_size = get_optimal_window_size(screen,
                                                           screen->frame_size);
        SDL_SetWindowSize(screen->window, optimal_size.width,
                          optimal_size.height);
        LOGD("Resized to optimal size");
    }
}