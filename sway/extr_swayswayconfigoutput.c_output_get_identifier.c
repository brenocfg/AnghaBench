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
struct wlr_output {char* make; char* model; char* serial; } ;
struct sway_output {struct wlr_output* wlr_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,char*) ; 

void output_get_identifier(char *identifier, size_t len,
		struct sway_output *output) {
	struct wlr_output *wlr_output = output->wlr_output;
	snprintf(identifier, len, "%s %s %s", wlr_output->make, wlr_output->model,
		wlr_output->serial);
}