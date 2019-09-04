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

/* Variables and functions */
 int /*<<< orphan*/  damage_surface_iterator ; 
 int /*<<< orphan*/  output_view_for_each_surface (struct sway_output*,struct sway_view*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  view_is_visible (struct sway_view*) ; 

void output_damage_from_view(struct sway_output *output,
		struct sway_view *view) {
	if (!view_is_visible(view)) {
		return;
	}
	bool whole = false;
	output_view_for_each_surface(output, view, damage_surface_iterator, &whole);
}