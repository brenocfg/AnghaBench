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
struct zxdg_output_v1 {int dummy; } ;
struct swaybar_output {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void xdg_output_handle_name(void *data,
		struct zxdg_output_v1 *xdg_output, const char *name) {
	struct swaybar_output *output = data;
	free(output->name);
	output->name = strdup(name);
}