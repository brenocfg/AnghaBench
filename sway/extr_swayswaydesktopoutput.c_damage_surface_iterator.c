#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ scale; } ;
struct wlr_surface {TYPE_1__ current; int /*<<< orphan*/  buffer_damage; } ;
struct wlr_box {int x; int width; int y; int height; } ;
struct sway_output {TYPE_2__* wlr_output; int /*<<< orphan*/  damage; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_4__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 scalar_t__ ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pixman_region32_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pixman_region32_not_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixman_region32_translate (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  scale_box (struct wlr_box*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_box_rotated_bounds (struct wlr_box*,struct wlr_box*,float) ; 
 int /*<<< orphan*/  wlr_output_damage_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_output_damage_add_box (int /*<<< orphan*/ ,struct wlr_box*) ; 
 int /*<<< orphan*/  wlr_output_schedule_frame (TYPE_2__*) ; 
 int /*<<< orphan*/  wlr_region_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wlr_region_rotated_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int,int) ; 
 int /*<<< orphan*/  wlr_region_scale (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_surface_get_effective_damage (struct wlr_surface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void damage_surface_iterator(struct sway_output *output,
		struct wlr_surface *surface, struct wlr_box *_box, float rotation,
		void *_data) {
	bool *data = _data;
	bool whole = *data;

	struct wlr_box box = *_box;
	scale_box(&box, output->wlr_output->scale);

	int center_x = box.x + box.width/2;
	int center_y = box.y + box.height/2;

	if (pixman_region32_not_empty(&surface->buffer_damage)) {
		pixman_region32_t damage;
		pixman_region32_init(&damage);
		wlr_surface_get_effective_damage(surface, &damage);
		wlr_region_scale(&damage, &damage, output->wlr_output->scale);
		if (ceil(output->wlr_output->scale) > surface->current.scale) {
			// When scaling up a surface, it'll become blurry so we need to
			// expand the damage region
			wlr_region_expand(&damage, &damage,
				ceil(output->wlr_output->scale) - surface->current.scale);
		}
		pixman_region32_translate(&damage, box.x, box.y);
		wlr_region_rotated_bounds(&damage, &damage, rotation,
			center_x, center_y);
		wlr_output_damage_add(output->damage, &damage);
		pixman_region32_fini(&damage);
	}

	if (whole) {
		wlr_box_rotated_bounds(&box, &box, rotation);
		wlr_output_damage_add_box(output->damage, &box);
	}

	wlr_output_schedule_frame(output->wlr_output);
}