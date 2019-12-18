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
typedef  size_t u_int ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* layout_sets ; 
 size_t nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
layout_set_lookup(const char *name)
{
	u_int	i;
	int	matched = -1;

	for (i = 0; i < nitems(layout_sets); i++) {
		if (strncmp(layout_sets[i].name, name, strlen(name)) == 0) {
			if (matched != -1)	/* ambiguous */
				return (-1);
			matched = i;
		}
	}

	return (matched);
}