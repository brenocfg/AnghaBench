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
struct options_table_entry {int dummy; } ;
struct options_entry {struct options_table_entry const* tableentry; } ;
struct options {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatalx (char*,char const*) ; 
 struct options_entry* options_get (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const struct options_table_entry *
options_parent_table_entry(struct options *oo, const char *s)
{
	struct options_entry	*o;

	if (oo->parent == NULL)
		fatalx("no parent options for %s", s);
	o = options_get(oo->parent, s);
	if (o == NULL)
		fatalx("%s not in parent options", s);
	return (o->tableentry);
}