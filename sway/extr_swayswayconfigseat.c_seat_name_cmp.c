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
struct seat_config {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

int seat_name_cmp(const void *item, const void *data) {
	const struct seat_config *sc = item;
	const char *name = data;
	return strcmp(sc->name, name);
}