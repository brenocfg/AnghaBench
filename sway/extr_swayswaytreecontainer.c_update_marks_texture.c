#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlr_texture {int dummy; } ;
struct wlr_renderer {int dummy; } ;
struct sway_output {TYPE_2__* wlr_output; } ;
struct sway_container {double title_height; TYPE_1__* marks; } ;
struct border_colors {int /*<<< orphan*/ * text; int /*<<< orphan*/ * background; } ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_6__ {int /*<<< orphan*/  font; } ;
struct TYPE_5__ {double scale; int /*<<< orphan*/  backend; } ;
struct TYPE_4__ {int length; char** items; } ;
typedef  int /*<<< orphan*/  PangoContext ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_ANTIALIAS_BEST ; 
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  WL_SHM_FORMAT_ARGB8888 ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int cairo_format_stride_for_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,int,int) ; 
 unsigned char* cairo_image_surface_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_antialias (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_rgba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_flush (int /*<<< orphan*/ *) ; 
 char* calloc (size_t,int) ; 
 TYPE_3__* config ; 
 struct sway_output* container_get_effective_output (struct sway_container*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,int,char*,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/ * pango_cairo_create_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 struct wlr_renderer* wlr_backend_get_renderer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_texture_destroy (struct wlr_texture*) ; 
 struct wlr_texture* wlr_texture_from_pixels (struct wlr_renderer*,int /*<<< orphan*/ ,int,int,int,unsigned char*) ; 

__attribute__((used)) static void update_marks_texture(struct sway_container *con,
		struct wlr_texture **texture, struct border_colors *class) {
	struct sway_output *output = container_get_effective_output(con);
	if (!output) {
		return;
	}
	if (*texture) {
		wlr_texture_destroy(*texture);
		*texture = NULL;
	}
	if (!con->marks->length) {
		return;
	}

	size_t len = 0;
	for (int i = 0; i < con->marks->length; ++i) {
		char *mark = con->marks->items[i];
		if (mark[0] != '_') {
			len += strlen(mark) + 2;
		}
	}
	char *buffer = calloc(len + 1, 1);
	char *part = malloc(len + 1);

	if (!sway_assert(buffer && part, "Unable to allocate memory")) {
		free(buffer);
		return;
	}

	for (int i = 0; i < con->marks->length; ++i) {
		char *mark = con->marks->items[i];
		if (mark[0] != '_') {
			sprintf(part, "[%s]", mark);
			strcat(buffer, part);
		}
	}
	free(part);

	double scale = output->wlr_output->scale;
	int width = 0;
	int height = con->title_height * scale;

	cairo_t *c = cairo_create(NULL);
	get_text_size(c, config->font, &width, NULL, NULL, scale, false,
			"%s", buffer);
	cairo_destroy(c);

	cairo_surface_t *surface = cairo_image_surface_create(
			CAIRO_FORMAT_ARGB32, width, height);
	cairo_t *cairo = cairo_create(surface);
	cairo_set_source_rgba(cairo, class->background[0], class->background[1],
			class->background[2], class->background[3]);
	cairo_paint(cairo);
	PangoContext *pango = pango_cairo_create_context(cairo);
	cairo_set_antialias(cairo, CAIRO_ANTIALIAS_BEST);
	cairo_set_source_rgba(cairo, class->text[0], class->text[1],
			class->text[2], class->text[3]);
	cairo_move_to(cairo, 0, 0);

	pango_printf(cairo, config->font, scale, false, "%s", buffer);

	cairo_surface_flush(surface);
	unsigned char *data = cairo_image_surface_get_data(surface);
	int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);
	struct wlr_renderer *renderer = wlr_backend_get_renderer(
			output->wlr_output->backend);
	*texture = wlr_texture_from_pixels(
			renderer, WL_SHM_FORMAT_ARGB8888, stride, width, height, data);
	cairo_surface_destroy(surface);
	g_object_unref(pango);
	cairo_destroy(cairo);
	free(buffer);
}