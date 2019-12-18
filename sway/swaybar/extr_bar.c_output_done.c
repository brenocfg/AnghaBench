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
struct wl_output {int dummy; } ;
struct swaybar_output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_output_dirty (struct swaybar_output*) ; 

__attribute__((used)) static void output_done(void *data, struct wl_output *wl_output) {
	struct swaybar_output *output = data;
	set_output_dirty(output);
}