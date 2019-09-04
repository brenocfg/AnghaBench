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
struct wlr_layer_surface_v1 {struct sway_layer_surface* data; } ;
struct sway_layer_surface {int dummy; } ;

/* Variables and functions */

struct sway_layer_surface *layer_from_wlr_layer_surface_v1(
		struct wlr_layer_surface_v1 *layer_surface) {
	return layer_surface->data;
}