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
struct screen {int /*<<< orphan*/  window; struct size windowed_window_size; scalar_t__ fullscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_SetWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_window_size(struct screen *screen, struct size new_size) {
    // setting the window size during fullscreen is implementation defined,
    // so apply the resize only after fullscreen is disabled
    if (screen->fullscreen) {
        // SDL_SetWindowSize will be called when fullscreen will be disabled
        screen->windowed_window_size = new_size;
    } else {
        SDL_SetWindowSize(screen->window, new_size.width, new_size.height);
    }
}