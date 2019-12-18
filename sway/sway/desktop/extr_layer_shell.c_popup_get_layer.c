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
struct sway_layer_surface {int dummy; } ;
struct sway_layer_popup {scalar_t__ parent_type; struct sway_layer_surface* parent_layer; struct sway_layer_popup* parent_popup; } ;

/* Variables and functions */
 scalar_t__ LAYER_PARENT_POPUP ; 

__attribute__((used)) static struct sway_layer_surface *popup_get_layer(
		struct sway_layer_popup *popup) {
	while (popup->parent_type == LAYER_PARENT_POPUP) {
		popup = popup->parent_popup;
	}
	return popup->parent_layer;
}