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
struct swaybar {int running; int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int wl_display_dispatch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void display_in(int fd, short mask, void *data) {
	struct swaybar *bar = data;
	if (wl_display_dispatch(bar->display) == -1) {
		bar->running = false;
	}
}