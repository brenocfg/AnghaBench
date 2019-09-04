#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct screen {int fullscreen; TYPE_1__ windowed_window_size; int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGD (char*,char*) ; 
 int /*<<< orphan*/  LOGW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 scalar_t__ SDL_SetWindowFullscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_SetWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WINDOW_FULLSCREEN_DESKTOP ; 
 TYPE_1__ get_native_window_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_render (struct screen*) ; 

void
screen_switch_fullscreen(struct screen *screen) {
    if (!screen->fullscreen) {
        // going to fullscreen, store the current windowed window size
        screen->windowed_window_size = get_native_window_size(screen->window);
    }
    uint32_t new_mode = screen->fullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (SDL_SetWindowFullscreen(screen->window, new_mode)) {
        LOGW("Could not switch fullscreen mode: %s", SDL_GetError());
        return;
    }

    screen->fullscreen = !screen->fullscreen;
    if (!screen->fullscreen) {
        // fullscreen disabled, restore expected windowed window size
        SDL_SetWindowSize(screen->window, screen->windowed_window_size.width,
                          screen->windowed_window_size.height);
    }

    LOGD("Switched to %s mode", screen->fullscreen ? "fullscreen" : "windowed");
    screen_render(screen);
}