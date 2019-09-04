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
struct input_config {int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

int input_identifier_cmp(const void *item, const void *data) {
	const struct input_config *ic = item;
	const char *identifier = data;
	return strcmp(ic->identifier, identifier);
}