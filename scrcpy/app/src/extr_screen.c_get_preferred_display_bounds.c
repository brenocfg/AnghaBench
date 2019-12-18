#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct size {void* height; void* width; } ;
struct TYPE_3__ {scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 scalar_t__ DISPLAY_MARGINS ; 
 scalar_t__ GET_DISPLAY_BOUNDS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LOGW (char*,int /*<<< orphan*/ ) ; 
 void* MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SDL_GetError () ; 

__attribute__((used)) static bool
get_preferred_display_bounds(struct size *bounds) {
    SDL_Rect rect;
#ifdef SCRCPY_SDL_HAS_GET_DISPLAY_USABLE_BOUNDS
# define GET_DISPLAY_BOUNDS(i, r) SDL_GetDisplayUsableBounds((i), (r))
#else
# define GET_DISPLAY_BOUNDS(i, r) SDL_GetDisplayBounds((i), (r))
#endif
    if (GET_DISPLAY_BOUNDS(0, &rect)) {
        LOGW("Could not get display usable bounds: %s", SDL_GetError());
        return false;
    }

    bounds->width = MAX(0, rect.w - DISPLAY_MARGINS);
    bounds->height = MAX(0, rect.h - DISPLAY_MARGINS);
    return true;
}