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
struct sway_workspace {char* name; } ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static bool _workspace_by_number(struct sway_workspace *ws, void *data) {
	char *name = data;
	char *ws_name = ws->name;
	while (isdigit(*name)) {
		if (*name++ != *ws_name++) {
			return false;
		}
	}
	return !isdigit(*ws_name);
}