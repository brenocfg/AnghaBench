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
typedef  int uint32_t ;
struct swaybar_tray {TYPE_2__* items; } ;
struct swaybar_output {int scale; TYPE_1__* bar; scalar_t__ height; } ;
struct swaybar_config {int tray_padding; scalar_t__ tray_outputs; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * items; } ;
struct TYPE_3__ {struct swaybar_tray* tray; struct swaybar_config* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_output ; 
 int list_seq_find (scalar_t__,int /*<<< orphan*/ ,struct swaybar_output*) ; 
 int render_sni (int /*<<< orphan*/ *,struct swaybar_output*,double*,int /*<<< orphan*/ ) ; 

uint32_t render_tray(cairo_t *cairo, struct swaybar_output *output, double *x) {
	struct swaybar_config *config = output->bar->config;
	if (config->tray_outputs) {
		if (list_seq_find(config->tray_outputs, cmp_output, output) == -1) {
			return 0;
		}
	} // else display on all

	if ((int) output->height*output->scale <= 2*config->tray_padding) {
		return 2*config->tray_padding + 1;
	}

	uint32_t max_height = 0;
	struct swaybar_tray *tray = output->bar->tray;
	for (int i = 0; i < tray->items->length; ++i) {
		uint32_t h = render_sni(cairo, output, x, tray->items->items[i]);
		if (h > max_height) {
			max_height = h;
		}
	}

	return max_height;
}