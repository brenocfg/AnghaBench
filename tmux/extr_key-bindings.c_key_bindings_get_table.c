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
struct key_table {char const* name; int references; int /*<<< orphan*/  key_bindings; } ;

/* Variables and functions */
 struct key_table* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key_table*) ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key_table*) ; 
 int /*<<< orphan*/  key_tables ; 
 struct key_table* xmalloc (int) ; 
 char const* xstrdup (char const*) ; 

struct key_table *
key_bindings_get_table(const char *name, int create)
{
	struct key_table	table_find, *table;

	table_find.name = name;
	table = RB_FIND(key_tables, &key_tables, &table_find);
	if (table != NULL || !create)
		return (table);

	table = xmalloc(sizeof *table);
	table->name = xstrdup(name);
	RB_INIT(&table->key_bindings);

	table->references = 1; /* one reference in key_tables */
	RB_INSERT(key_tables, &key_tables, table);

	return (table);
}