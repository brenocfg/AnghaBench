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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct screen {TYPE_1__ frame_size; int /*<<< orphan*/  window; int /*<<< orphan*/  fullscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  SDL_SetWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
screen_resize_to_pixel_perfect(struct screen *screen) {
    if (!screen->fullscreen) {
        SDL_SetWindowSize(screen->window, screen->frame_size.width,
                          screen->frame_size.height);
        LOGD("Resized to pixel-perfect");
    }
}