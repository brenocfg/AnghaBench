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
struct swaybar_sni {struct swaybar_sni* icon_theme_path; struct swaybar_sni* menu; int /*<<< orphan*/  attention_icon_pixmap; struct swaybar_sni* attention_icon_name; int /*<<< orphan*/  icon_pixmap; struct swaybar_sni* icon_name; struct swaybar_sni* status; struct swaybar_sni* path; struct swaybar_sni* service; struct swaybar_sni* watcher_id; int /*<<< orphan*/  new_status_slot; int /*<<< orphan*/  new_attention_icon_slot; int /*<<< orphan*/  new_icon_slot; int /*<<< orphan*/  icon; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct swaybar_sni*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 

void destroy_sni(struct swaybar_sni *sni) {
	if (!sni) {
		return;
	}

	cairo_surface_destroy(sni->icon);

	sd_bus_slot_unref(sni->new_icon_slot);
	sd_bus_slot_unref(sni->new_attention_icon_slot);
	sd_bus_slot_unref(sni->new_status_slot);

	free(sni->watcher_id);
	free(sni->service);
	free(sni->path);
	free(sni->status);
	free(sni->icon_name);
	list_free_items_and_destroy(sni->icon_pixmap);
	free(sni->attention_icon_name);
	list_free_items_and_destroy(sni->attention_icon_pixmap);
	free(sni->menu);
	free(sni->icon_theme_path);
	free(sni);
}