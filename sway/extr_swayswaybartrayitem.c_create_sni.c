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
struct swaybar_tray {int dummy; } ;
struct swaybar_sni {char* interface; int /*<<< orphan*/  new_status_slot; int /*<<< orphan*/  new_attention_icon_slot; int /*<<< orphan*/  new_icon_slot; int /*<<< orphan*/  menu; int /*<<< orphan*/  item_is_menu; int /*<<< orphan*/  attention_icon_pixmap; int /*<<< orphan*/  attention_icon_name; int /*<<< orphan*/  icon_pixmap; int /*<<< orphan*/  icon_name; int /*<<< orphan*/  status; int /*<<< orphan*/  icon_theme_path; void* path; void* service; void* watcher_id; struct swaybar_tray* tray; } ;

/* Variables and functions */
 struct swaybar_sni* calloc (int,int) ; 
 int /*<<< orphan*/  handle_new_attention_icon ; 
 int /*<<< orphan*/  handle_new_icon ; 
 int /*<<< orphan*/  handle_new_status ; 
 int /*<<< orphan*/  sni_get_property_async (struct swaybar_sni*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sni_match_signal (struct swaybar_sni*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 void* strdup (char*) ; 
 void* strndup (char*,int) ; 

struct swaybar_sni *create_sni(char *id, struct swaybar_tray *tray) {
	struct swaybar_sni *sni = calloc(1, sizeof(struct swaybar_sni));
	if (!sni) {
		return NULL;
	}
	sni->tray = tray;
	sni->watcher_id = strdup(id);
	char *path_ptr = strchr(id, '/');
	if (!path_ptr) {
		sni->service = strdup(id);
		sni->path = strdup("/StatusNotifierItem");
		sni->interface = "org.freedesktop.StatusNotifierItem";
	} else {
		sni->service = strndup(id, path_ptr - id);
		sni->path = strdup(path_ptr);
		sni->interface = "org.kde.StatusNotifierItem";
		sni_get_property_async(sni, "IconThemePath", "s", &sni->icon_theme_path);
	}

	// Ignored: Category, Id, Title, WindowId, OverlayIconName,
	//          OverlayIconPixmap, AttentionMovieName, ToolTip
	sni_get_property_async(sni, "Status", "s", &sni->status);
	sni_get_property_async(sni, "IconName", "s", &sni->icon_name);
	sni_get_property_async(sni, "IconPixmap", NULL, &sni->icon_pixmap);
	sni_get_property_async(sni, "AttentionIconName", "s", &sni->attention_icon_name);
	sni_get_property_async(sni, "AttentionIconPixmap", NULL, &sni->attention_icon_pixmap);
	sni_get_property_async(sni, "ItemIsMenu", "b", &sni->item_is_menu);
	sni_get_property_async(sni, "Menu", "o", &sni->menu);

	sni_match_signal(sni, &sni->new_icon_slot, "NewIcon", handle_new_icon);
	sni_match_signal(sni, &sni->new_attention_icon_slot, "NewAttentionIcon",
			handle_new_attention_icon);
	sni_match_signal(sni, &sni->new_status_slot, "NewStatus", handle_new_status);

	return sni;
}