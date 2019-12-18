#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swaynag_type {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int length; struct swaynag_type** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

struct swaynag_type *swaynag_type_get(list_t *types, char *name) {
	for (int i = 0; i < types->length; i++) {
		struct swaynag_type *type = types->items[i];
		if (strcasecmp(type->name, name) == 0) {
			return type;
		}
	}
	return NULL;
}