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
union options_value {int /*<<< orphan*/  string; } ;
struct options_entry {int dummy; } ;
struct options_array_item {int dummy; } ;
struct options {int dummy; } ;
struct environ_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct environ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  environ_clear (struct environ*,int /*<<< orphan*/ ) ; 
 struct environ_entry* environ_find (struct environ*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  environ_set (struct environ*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct options_array_item* options_array_first (struct options_entry*) ; 
 union options_value* options_array_item_value (struct options_array_item*) ; 
 struct options_array_item* options_array_next (struct options_array_item*) ; 
 struct options_entry* options_get (struct options*,char*) ; 

void
environ_update(struct options *oo, struct environ *src, struct environ *dst)
{
	struct environ_entry		*envent;
	struct options_entry		*o;
	struct options_array_item	*a;
	union options_value		*ov;

	o = options_get(oo, "update-environment");
	if (o == NULL)
		return;
	a = options_array_first(o);
	while (a != NULL) {
		ov = options_array_item_value(a);
		if ((envent = environ_find(src, ov->string)) == NULL)
			environ_clear(dst, ov->string);
		else
			environ_set(dst, envent->name, "%s", envent->value);
		a = options_array_next(a);
	}
}