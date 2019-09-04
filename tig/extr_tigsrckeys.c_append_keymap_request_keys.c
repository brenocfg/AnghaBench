#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct keymap {int size; TYPE_1__** data; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {int request; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_key (char*,size_t*,TYPE_1__*,int) ; 

__attribute__((used)) static bool
append_keymap_request_keys(char *buf, size_t *pos, enum request request,
			   const struct keymap *keymap, bool all)
{
	int i;

	for (i = 0; i < keymap->size; i++) {
		if (keymap->data[i]->request == request) {
			if (!append_key(buf, pos, keymap->data[i], all))
				return false;
			if (!all)
				break;
		}
	}

	return true;
}