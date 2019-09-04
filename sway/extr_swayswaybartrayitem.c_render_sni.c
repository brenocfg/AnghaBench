#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct swaybar_sni {int min_size; int max_size; char* status; char* attention_icon_name; char* icon_name; int /*<<< orphan*/  watcher_id; int /*<<< orphan*/ * icon; TYPE_4__* icon_pixmap; TYPE_4__* attention_icon_pixmap; scalar_t__ icon_theme_path; TYPE_1__* tray; } ;
struct swaybar_pixmap {int size; int /*<<< orphan*/  pixels; } ;
struct swaybar_output {int height; int scale; int /*<<< orphan*/  hotspots; TYPE_3__* bar; } ;
struct swaybar_hotspot {double x; int width; int height; int /*<<< orphan*/  link; int /*<<< orphan*/  data; int /*<<< orphan*/  (* destroy ) (char*) ;int /*<<< orphan*/  callback; int /*<<< orphan*/  y; } ;
struct TYPE_8__ {int length; struct swaybar_pixmap** items; } ;
typedef  TYPE_4__ list_t ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
typedef  int /*<<< orphan*/  cairo_operator_t ;
struct TYPE_7__ {TYPE_2__* config; } ;
struct TYPE_6__ {int tray_padding; int /*<<< orphan*/  icon_theme; } ;
struct TYPE_5__ {int /*<<< orphan*/  basedirs; int /*<<< orphan*/  themes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_CLEAR ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_OVER ; 
 int /*<<< orphan*/  cairo_arc (int /*<<< orphan*/ *,double,double,double,double,double) ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_format_stride_for_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cairo_get_operator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * cairo_image_surface_create_for_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int cairo_image_surface_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_scale (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,double,int,int,int) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_set_line_width (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cairo_stroke (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_translate (int /*<<< orphan*/ *,int,int) ; 
 struct swaybar_hotspot* calloc (int,int) ; 
 char* find_icon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int*,int*) ; 
 char* find_icon_in_dir (char*,scalar_t__,int*,int*) ; 
 int floor (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  icon_hotspot_callback ; 
 int /*<<< orphan*/ * load_background_image (char*) ; 
 scalar_t__ sni_ready (struct swaybar_sni*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint32_t render_sni(cairo_t *cairo, struct swaybar_output *output, double *x,
		struct swaybar_sni *sni) {
	uint32_t height = output->height * output->scale;
	int padding = output->bar->config->tray_padding;
	int ideal_size = height - 2*padding;
	if ((ideal_size < sni->min_size || ideal_size > sni->max_size) && sni_ready(sni)) {
		bool icon_found = false;
		char *icon_name = sni->status[0] == 'N' ?
			sni->attention_icon_name : sni->icon_name;
		if (icon_name) {
			char *icon_path = find_icon(sni->tray->themes, sni->tray->basedirs,
					icon_name, ideal_size, output->bar->config->icon_theme,
					&sni->min_size, &sni->max_size);
			if (!icon_path && sni->icon_theme_path) {
				icon_path = find_icon_in_dir(icon_name, sni->icon_theme_path,
						&sni->min_size, &sni->max_size);
			}
			if (icon_path) {
				cairo_surface_destroy(sni->icon);
				sni->icon = load_background_image(icon_path);
				free(icon_path);
				icon_found = true;
			}
		}
		if (!icon_found) {
			list_t *pixmaps = sni->status[0] == 'N' ?
				sni->attention_icon_pixmap : sni->icon_pixmap;
			if (pixmaps) {
				int idx = -1;
				unsigned smallest_error = -1; // UINT_MAX
				for (int i = 0; i < pixmaps->length; ++i) {
					struct swaybar_pixmap *pixmap = pixmaps->items[i];
					unsigned error = (ideal_size - pixmap->size) *
						(ideal_size < pixmap->size ? -1 : 1);
					if (error < smallest_error) {
						smallest_error = error;
						idx = i;
					}
				}
				struct swaybar_pixmap *pixmap = pixmaps->items[idx];
				cairo_surface_destroy(sni->icon);
				sni->icon = cairo_image_surface_create_for_data(pixmap->pixels,
						CAIRO_FORMAT_ARGB32, pixmap->size, pixmap->size,
						cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, pixmap->size));
			}
		}
	}

	int icon_size;
	cairo_surface_t *icon;
	if (sni->icon) {
		int actual_size = cairo_image_surface_get_height(sni->icon);
		icon_size = actual_size < ideal_size ?
			actual_size*(ideal_size/actual_size) : ideal_size;
		icon = cairo_image_surface_scale(sni->icon, icon_size, icon_size);
	} else { // draw a :(
		icon_size = ideal_size*0.8;
		icon = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, icon_size, icon_size);
		cairo_t *cairo_icon = cairo_create(icon);
		cairo_set_source_u32(cairo_icon, 0xFF0000FF);
		cairo_translate(cairo_icon, icon_size/2, icon_size/2);
		cairo_scale(cairo_icon, icon_size/2, icon_size/2);
		cairo_arc(cairo_icon, 0, 0, 1, 0, 7);
		cairo_fill(cairo_icon);
		cairo_set_operator(cairo_icon, CAIRO_OPERATOR_CLEAR);
		cairo_arc(cairo_icon, 0.35, -0.3, 0.1, 0, 7);
		cairo_fill(cairo_icon);
		cairo_arc(cairo_icon, -0.35, -0.3, 0.1, 0, 7);
		cairo_fill(cairo_icon);
		cairo_arc(cairo_icon, 0, 0.75, 0.5, 3.71238898038469, 5.71238898038469);
		cairo_set_line_width(cairo_icon, 0.1);
		cairo_stroke(cairo_icon);
		cairo_destroy(cairo_icon);
	}

	int padded_size = icon_size + 2*padding;
	*x -= padded_size;
	int y = floor((height - padded_size) / 2.0);

	cairo_operator_t op = cairo_get_operator(cairo);
	cairo_set_operator(cairo, CAIRO_OPERATOR_OVER);
	cairo_set_source_surface(cairo, icon, *x + padding, y + padding);
	cairo_rectangle(cairo, *x, y, padded_size, padded_size);
	cairo_fill(cairo);
	cairo_set_operator(cairo, op);

	cairo_surface_destroy(icon);

	struct swaybar_hotspot *hotspot = calloc(1, sizeof(struct swaybar_hotspot));
	hotspot->x = *x;
	hotspot->y = 0;
	hotspot->width = height;
	hotspot->height = height;
	hotspot->callback = icon_hotspot_callback;
	hotspot->destroy = free;
	hotspot->data = strdup(sni->watcher_id);
	wl_list_insert(&output->hotspots, &hotspot->link);

	return output->height;
}