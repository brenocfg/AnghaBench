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
struct keymap {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct keymap*) ; 
 struct keymap* keymaps ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,size_t) ; 

struct keymap *
get_keymap(const char *name, size_t namelen)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(keymaps); i++)
		if (!strncasecmp(keymaps[i].name, name, namelen))
			return &keymaps[i];

	return NULL;
}