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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOGC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  SDL_EnableScreenSaver () ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH ; 
 int /*<<< orphan*/  SDL_HINT_RENDER_SCALE_QUALITY ; 
 int /*<<< orphan*/  SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS ; 
 int /*<<< orphan*/  SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR ; 
 int /*<<< orphan*/  SDL_INIT_EVENTS ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit ; 
 int /*<<< orphan*/  SDL_SetHint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
sdl_init_and_configure(bool display) {
    uint32_t flags = display ? SDL_INIT_VIDEO : SDL_INIT_EVENTS;
    if (SDL_Init(flags)) {
        LOGC("Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    atexit(SDL_Quit);

    if (!display) {
        return true;
    }

    // Use the best available scale quality
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2")) {
        LOGW("Could not enable bilinear filtering");
    }

#ifdef SCRCPY_SDL_HAS_HINT_MOUSE_FOCUS_CLICKTHROUGH
    // Handle a click to gain focus as any other click
    if (!SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1")) {
        LOGW("Could not enable mouse focus clickthrough");
    }
#endif

#ifdef SCRCPY_SDL_HAS_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR
    // Disable compositor bypassing on X11
    if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
        LOGW("Could not disable X11 compositor bypass");
    }
#endif

    // Do not minimize on focus loss
    if (!SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0")) {
        LOGW("Could not disable minimize on focus loss");
    }

    // Do not disable the screensaver when scrcpy is running
    SDL_EnableScreenSaver();

    return true;
}