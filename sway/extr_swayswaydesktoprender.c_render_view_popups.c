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
struct sway_view {int dummy; } ;
struct sway_output {int dummy; } ;
struct render_data {float alpha; int /*<<< orphan*/ * damage; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;

/* Variables and functions */
 int /*<<< orphan*/  output_view_for_each_popup (struct sway_output*,struct sway_view*,int /*<<< orphan*/ ,struct render_data*) ; 
 int /*<<< orphan*/  render_popup_iterator ; 

__attribute__((used)) static void render_view_popups(struct sway_view *view,
		struct sway_output *output, pixman_region32_t *damage, float alpha) {
	struct render_data data = {
		.damage = damage,
		.alpha = alpha,
	};
	output_view_for_each_popup(output, view, render_popup_iterator, &data);
}