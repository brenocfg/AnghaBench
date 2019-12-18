#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl_cursor {TYPE_1__** images; } ;
struct swaynag_pointer {int /*<<< orphan*/  cursor_surface; TYPE_1__* cursor_image; int /*<<< orphan*/  serial; int /*<<< orphan*/  pointer; scalar_t__ cursor_theme; } ;
struct swaynag {unsigned int scale; int /*<<< orphan*/  shm; struct swaynag_pointer pointer; } ;
struct TYPE_2__ {int hotspot_x; int hotspot_y; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT32_MAX ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 scalar_t__ strlen (char const*) ; 
 unsigned int strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  wl_cursor_image_get_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (scalar_t__) ; 
 struct wl_cursor* wl_cursor_theme_get_cursor (scalar_t__,char*) ; 
 scalar_t__ wl_cursor_theme_load (char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wl_surface_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_damage_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void update_cursor(struct swaynag *swaynag) {
	struct swaynag_pointer *pointer = &swaynag->pointer;
	if (swaynag->pointer.cursor_theme) {
		wl_cursor_theme_destroy(swaynag->pointer.cursor_theme);
	}
	const char *cursor_theme = getenv("XCURSOR_THEME");
	unsigned cursor_size = 24;
	const char *env_cursor_size = getenv("XCURSOR_SIZE");
	if (env_cursor_size && strlen(env_cursor_size) > 0) {
		errno = 0;
		char *end;
		unsigned size = strtoul(env_cursor_size, &end, 10);
		if (!*end && errno == 0) {
			cursor_size = size;
		}
	}
	pointer->cursor_theme = wl_cursor_theme_load(
		cursor_theme, cursor_size * swaynag->scale, swaynag->shm);
	struct wl_cursor *cursor =
		wl_cursor_theme_get_cursor(pointer->cursor_theme, "left_ptr");
	pointer->cursor_image = cursor->images[0];
	wl_surface_set_buffer_scale(pointer->cursor_surface,
			swaynag->scale);
	wl_surface_attach(pointer->cursor_surface,
			wl_cursor_image_get_buffer(pointer->cursor_image), 0, 0);
	wl_pointer_set_cursor(pointer->pointer, pointer->serial,
			pointer->cursor_surface,
			pointer->cursor_image->hotspot_x / swaynag->scale,
			pointer->cursor_image->hotspot_y / swaynag->scale);
	wl_surface_damage_buffer(pointer->cursor_surface, 0, 0,
			INT32_MAX, INT32_MAX);
	wl_surface_commit(pointer->cursor_surface);
}