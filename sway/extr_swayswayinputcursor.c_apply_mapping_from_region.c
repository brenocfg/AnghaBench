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
struct wlr_input_device {double width_mm; double height_mm; } ;
struct input_config_mapped_from_region {double x1; double x2; double y1; double y2; scalar_t__ mm; } ;

/* Variables and functions */
 double apply_mapping_from_coord (double,double,double) ; 

__attribute__((used)) static void apply_mapping_from_region(struct wlr_input_device *device,
		struct input_config_mapped_from_region *region, double *x, double *y) {
	double x1 = region->x1, x2 = region->x2;
	double y1 = region->y1, y2 = region->y2;

	if (region->mm) {
		if (device->width_mm == 0 || device->height_mm == 0) {
			return;
		}
		x1 /= device->width_mm;
		x2 /= device->width_mm;
		y1 /= device->height_mm;
		y2 /= device->height_mm;
	}

	*x = apply_mapping_from_coord(x1, x2, *x);
	*y = apply_mapping_from_coord(y1, y2, *y);
}