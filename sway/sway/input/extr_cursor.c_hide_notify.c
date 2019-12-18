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
struct sway_cursor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_hide (struct sway_cursor*) ; 

__attribute__((used)) static int hide_notify(void *data) {
	struct sway_cursor *cursor = data;
	cursor_hide(cursor);
	return 1;
}