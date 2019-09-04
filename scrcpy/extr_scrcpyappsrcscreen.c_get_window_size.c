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
struct size {int dummy; } ;
struct screen {int /*<<< orphan*/  window; struct size windowed_window_size; scalar_t__ fullscreen; } ;

/* Variables and functions */
 struct size get_native_window_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct size
get_window_size(const struct screen *screen) {
    if (screen->fullscreen) {
        return screen->windowed_window_size;
    }
    return get_native_window_size(screen->window);
}