#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct swaybar_sni {int /*<<< orphan*/  watcher_id; } ;
struct swaybar_pixmap {int size; scalar_t__ pixels; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_6__ {int length; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 TYPE_1__* create_list () ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct swaybar_pixmap*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (TYPE_1__*) ; 
 struct swaybar_pixmap* malloc (int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ sd_bus_message_at_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,char*) ; 
 int /*<<< orphan*/  sd_bus_message_exit_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int sd_bus_message_read_array (int /*<<< orphan*/ *,char,void const**,size_t*) ; 
 int strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static int read_pixmap(sd_bus_message *msg, struct swaybar_sni *sni,
		const char *prop, list_t **dest) {
	int ret = sd_bus_message_enter_container(msg, 'a', "(iiay)");
	if (ret < 0) {
		sway_log(SWAY_ERROR, "%s %s: %s", sni->watcher_id, prop, strerror(-ret));
		return ret;
	}

	if (sd_bus_message_at_end(msg, 0)) {
		sway_log(SWAY_DEBUG, "%s %s no. of icons = 0", sni->watcher_id, prop);
		return ret;
	}

	list_t *pixmaps = create_list();
	if (!pixmaps) {
		return -12; // -ENOMEM
	}

	while (!sd_bus_message_at_end(msg, 0)) {
		ret = sd_bus_message_enter_container(msg, 'r', "iiay");
		if (ret < 0) {
			sway_log(SWAY_ERROR, "%s %s: %s", sni->watcher_id, prop, strerror(-ret));
			goto error;
		}

		int width, height;
		ret = sd_bus_message_read(msg, "ii", &width, &height);
		if (ret < 0) {
			sway_log(SWAY_ERROR, "%s %s: %s", sni->watcher_id, prop, strerror(-ret));
			goto error;
		}

		const void *pixels;
		size_t npixels;
		ret = sd_bus_message_read_array(msg, 'y', &pixels, &npixels);
		if (ret < 0) {
			sway_log(SWAY_ERROR, "%s %s: %s", sni->watcher_id, prop, strerror(-ret));
			goto error;
		}

		if (height > 0 && width == height) {
			sway_log(SWAY_DEBUG, "%s %s: found icon w:%d h:%d", sni->watcher_id, prop, width, height);
			struct swaybar_pixmap *pixmap =
				malloc(sizeof(struct swaybar_pixmap) + npixels);
			pixmap->size = height;

			// convert from network byte order to host byte order
			for (int i = 0; i < height * width; ++i) {
				((uint32_t *)pixmap->pixels)[i] = ntohl(((uint32_t *)pixels)[i]);
			}

			list_add(pixmaps, pixmap);
		} else {
			sway_log(SWAY_DEBUG, "%s %s: discard invalid icon w:%d h:%d", sni->watcher_id, prop, width, height);
		}

		sd_bus_message_exit_container(msg);
	}

	if (pixmaps->length < 1) {
		sway_log(SWAY_DEBUG, "%s %s no. of icons = 0", sni->watcher_id, prop);
		goto error;
	}

	list_free_items_and_destroy(*dest);
	*dest = pixmaps;
	sway_log(SWAY_DEBUG, "%s %s no. of icons = %d", sni->watcher_id, prop,
			pixmaps->length);

	return ret;
error:
	list_free_items_and_destroy(pixmaps);
	return ret;
}