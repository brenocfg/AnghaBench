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
struct swaybar_output {scalar_t__ name; scalar_t__ identifier; } ;

/* Variables and functions */
 int strcmp (void const*,scalar_t__) ; 

__attribute__((used)) static int cmp_output(const void *item, const void *cmp_to) {
	const struct swaybar_output *output = cmp_to;
	if (output->identifier && strcmp(item, output->identifier) == 0) {
		return 0;
	}
	return strcmp(item, output->name);
}