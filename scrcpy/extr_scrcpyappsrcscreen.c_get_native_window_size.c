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
struct size {int width; int height; } ;
typedef  int /*<<< orphan*/  SDL_Window ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static struct size
get_native_window_size(SDL_Window *window) {
    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);

    struct size size;
    size.width = width;
    size.height = height;
    return size;
}