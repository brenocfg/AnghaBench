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
struct TYPE_3__ {int x; int y; } ;
typedef  int /*<<< orphan*/  SDL_Renderer ;
typedef  TYPE_1__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_RenderGetScale (int /*<<< orphan*/ *,float*,float*) ; 
 int /*<<< orphan*/  SDL_RenderGetViewport (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
convert_to_renderer_coordinates(SDL_Renderer *renderer, int *x, int *y) {
    SDL_Rect viewport;
    float scale_x, scale_y;
    SDL_RenderGetViewport(renderer, &viewport);
    SDL_RenderGetScale(renderer, &scale_x, &scale_y);
    *x = (int) (*x / scale_x) - viewport.x;
    *y = (int) (*y / scale_y) - viewport.y;
}