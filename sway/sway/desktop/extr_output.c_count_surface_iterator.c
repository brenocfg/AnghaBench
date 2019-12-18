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
struct wlr_surface {int dummy; } ;
struct wlr_box {int dummy; } ;
struct sway_output {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void count_surface_iterator(struct sway_output *output,
		struct wlr_surface *surface, struct wlr_box *_box, float rotation,
		void *data) {
	size_t *n = data;
	(*n)++;
}