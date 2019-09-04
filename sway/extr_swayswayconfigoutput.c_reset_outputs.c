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
struct output_config {int dummy; } ;
struct TYPE_4__ {TYPE_1__* output_configs; } ;
struct TYPE_3__ {struct output_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_output_config_to_outputs (struct output_config*) ; 
 TYPE_2__* config ; 
 int list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  new_output_config (char*) ; 
 int /*<<< orphan*/  output_name_cmp ; 
 struct output_config* store_output_config (int /*<<< orphan*/ ) ; 

void reset_outputs(void) {
	struct output_config *oc = NULL;
	int i = list_seq_find(config->output_configs, output_name_cmp, "*");
	if (i >= 0) {
		oc = config->output_configs->items[i];
	} else {
		oc = store_output_config(new_output_config("*"));
	}
	apply_output_config_to_outputs(oc);
}