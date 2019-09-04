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
struct zwlr_layer_surface_v1 {int dummy; } ;
struct swaybar_output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  swaybar_output_free (struct swaybar_output*) ; 

__attribute__((used)) static void layer_surface_closed(void *_output,
		struct zwlr_layer_surface_v1 *surface) {
	struct swaybar_output *output = _output;
	swaybar_output_free(output);
}