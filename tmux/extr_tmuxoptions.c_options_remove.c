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
struct options_entry {int /*<<< orphan*/  value; struct options* owner; } ;
struct options {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 scalar_t__ OPTIONS_IS_ARRAY (struct options_entry*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_entry*) ; 
 int /*<<< orphan*/  free (struct options_entry*) ; 
 int /*<<< orphan*/  options_array_clear (struct options_entry*) ; 
 int /*<<< orphan*/  options_tree ; 
 int /*<<< orphan*/  options_value_free (struct options_entry*,int /*<<< orphan*/ *) ; 

void
options_remove(struct options_entry *o)
{
	struct options	*oo = o->owner;

	if (OPTIONS_IS_ARRAY(o))
		options_array_clear(o);
	else
		options_value_free(o, &o->value);
	RB_REMOVE(options_tree, &oo->tree, o);
	free(o);
}