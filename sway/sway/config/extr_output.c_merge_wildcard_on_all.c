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
struct output_config {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* output_configs; } ;
struct TYPE_3__ {int length; struct output_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  merge_output_config (struct output_config*,struct output_config*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void merge_wildcard_on_all(struct output_config *wildcard) {
	for (int i = 0; i < config->output_configs->length; i++) {
		struct output_config *oc = config->output_configs->items[i];
		if (strcmp(wildcard->name, oc->name) != 0) {
			sway_log(SWAY_DEBUG, "Merging output * config on %s", oc->name);
			merge_output_config(oc, wildcard);
		}
	}
}