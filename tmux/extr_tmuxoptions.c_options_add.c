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
struct options_entry {int /*<<< orphan*/  name; struct options* owner; } ;
struct options {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_entry*) ; 
 struct options_entry* options_get_only (struct options*,char const*) ; 
 int /*<<< orphan*/  options_remove (struct options_entry*) ; 
 int /*<<< orphan*/  options_tree ; 
 struct options_entry* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct options_entry *
options_add(struct options *oo, const char *name)
{
	struct options_entry	*o;

	o = options_get_only(oo, name);
	if (o != NULL)
		options_remove(o);

	o = xcalloc(1, sizeof *o);
	o->owner = oo;
	o->name = xstrdup(name);

	RB_INSERT(options_tree, &oo->tree, o);
	return (o);
}