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
struct TYPE_3__ {int length; int /*<<< orphan*/ * items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 char* find_icon_in_dir (char*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static char *find_fallback_icon(list_t *basedirs, char *name, int *min_size,
		int *max_size) {
	for (int i = 0; i < basedirs->length; ++i) {
		char *icon = find_icon_in_dir(name, basedirs->items[i], min_size, max_size);
		if (icon) {
			return icon;
		}
	}
	return NULL;
}