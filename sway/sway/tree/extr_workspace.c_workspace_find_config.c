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
struct workspace_config {int /*<<< orphan*/  workspace; } ;
struct TYPE_4__ {TYPE_1__* workspace_configs; } ;
struct TYPE_3__ {int length; struct workspace_config** items; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct workspace_config *workspace_find_config(const char *ws_name) {
	for (int i = 0; i < config->workspace_configs->length; ++i) {
		struct workspace_config *wsc = config->workspace_configs->items[i];
		if (strcmp(wsc->workspace, ws_name) == 0) {
			return wsc;
		}
	}
	return NULL;
}