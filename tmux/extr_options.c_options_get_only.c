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
struct options_entry {char const* name; } ;
struct options {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 struct options_entry* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct options_entry*) ; 
 int /*<<< orphan*/  options_tree ; 

struct options_entry *
options_get_only(struct options *oo, const char *name)
{
	struct options_entry	o;

	o.name = name;
	return (RB_FIND(options_tree, &oo->tree, &o));
}