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
struct options_entry {int dummy; } ;
struct options {struct options* parent; } ;

/* Variables and functions */
 struct options_entry* options_get_only (struct options*,char const*) ; 

struct options_entry *
options_get(struct options *oo, const char *name)
{
	struct options_entry	*o;

	o = options_get_only(oo, name);
	while (o == NULL) {
		oo = oo->parent;
		if (oo == NULL)
			break;
		o = options_get_only(oo, name);
	}
	return (o);
}