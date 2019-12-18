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
struct swaybar_sni {int /*<<< orphan*/  watcher_id; int /*<<< orphan*/  interface; int /*<<< orphan*/  path; int /*<<< orphan*/  service; TYPE_1__* tray; } ;
struct get_property_data {char const* prop; char const* type; void* dest; struct swaybar_sni* sni; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  get_property_callback ; 
 struct get_property_data* malloc (int) ; 
 int sd_bus_call_method_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,struct get_property_data*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sni_get_property_async(struct swaybar_sni *sni, const char *prop,
		const char *type, void *dest) {
	struct get_property_data *data = malloc(sizeof(struct get_property_data));
	data->sni = sni;
	data->prop = prop;
	data->type = type;
	data->dest = dest;
	int ret = sd_bus_call_method_async(sni->tray->bus, NULL, sni->service,
			sni->path, "org.freedesktop.DBus.Properties", "Get",
			get_property_callback, data, "ss", sni->interface, prop);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "%s %s: %s", sni->watcher_id, prop, strerror(-ret));
	}
}