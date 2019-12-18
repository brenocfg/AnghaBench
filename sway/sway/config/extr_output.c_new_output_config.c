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
struct output_config {int enabled; int width; int height; int refresh_rate; int custom_mode; int x; int y; int scale; int transform; int /*<<< orphan*/  subpixel; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL_OUTPUT_SUBPIXEL_UNKNOWN ; 
 struct output_config* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct output_config*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

struct output_config *new_output_config(const char *name) {
	struct output_config *oc = calloc(1, sizeof(struct output_config));
	if (oc == NULL) {
		return NULL;
	}
	oc->name = strdup(name);
	if (oc->name == NULL) {
		free(oc);
		return NULL;
	}
	oc->enabled = -1;
	oc->width = oc->height = -1;
	oc->refresh_rate = -1;
	oc->custom_mode = -1;
	oc->x = oc->y = -1;
	oc->scale = -1;
	oc->transform = -1;
	oc->subpixel = WL_OUTPUT_SUBPIXEL_UNKNOWN;
	return oc;
}