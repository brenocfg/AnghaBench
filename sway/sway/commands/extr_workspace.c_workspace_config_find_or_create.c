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
struct TYPE_3__ {void* left; void* bottom; void* right; void* top; } ;
struct workspace_config {TYPE_1__ gaps_outer; void* gaps_inner; int /*<<< orphan*/  outputs; int /*<<< orphan*/  workspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  workspace_configs; } ;

/* Variables and functions */
 void* INT_MIN ; 
 struct workspace_config* calloc (int,int) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  create_list () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct workspace_config*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 struct workspace_config* workspace_find_config (char*) ; 

__attribute__((used)) static struct workspace_config *workspace_config_find_or_create(char *ws_name) {
	struct workspace_config *wsc = workspace_find_config(ws_name);
	if (wsc) {
		return wsc;
	}
	wsc = calloc(1, sizeof(struct workspace_config));
	if (!wsc) {
		return NULL;
	}
	wsc->workspace = strdup(ws_name);
	wsc->outputs = create_list();
	wsc->gaps_inner = INT_MIN;
	wsc->gaps_outer.top = INT_MIN;
	wsc->gaps_outer.right = INT_MIN;
	wsc->gaps_outer.bottom = INT_MIN;
	wsc->gaps_outer.left = INT_MIN;
	list_add(config->workspace_configs, wsc);
	return wsc;
}