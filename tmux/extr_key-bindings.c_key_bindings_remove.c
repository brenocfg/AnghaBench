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
struct key_table {int key; int /*<<< orphan*/  key_bindings; int /*<<< orphan*/  cmdlist; } ;
struct key_binding {int key; int /*<<< orphan*/  key_bindings; int /*<<< orphan*/  cmdlist; } ;
typedef  int key_code ;

/* Variables and functions */
 int KEYC_XTERM ; 
 scalar_t__ RB_EMPTY (int /*<<< orphan*/ *) ; 
 struct key_table* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key_table*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key_table*) ; 
 int /*<<< orphan*/  cmd_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct key_table*) ; 
 int /*<<< orphan*/  key_bindings ; 
 struct key_table* key_bindings_get_table (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_bindings_unref_table (struct key_table*) ; 
 int /*<<< orphan*/  key_tables ; 

void
key_bindings_remove(const char *name, key_code key)
{
	struct key_table	*table;
	struct key_binding	 bd_find, *bd;

	table = key_bindings_get_table(name, 0);
	if (table == NULL)
		return;

	bd_find.key = (key & ~KEYC_XTERM);
	bd = RB_FIND(key_bindings, &table->key_bindings, &bd_find);
	if (bd == NULL)
		return;

	RB_REMOVE(key_bindings, &table->key_bindings, bd);
	cmd_list_free(bd->cmdlist);
	free(bd);

	if (RB_EMPTY(&table->key_bindings)) {
		RB_REMOVE(key_tables, &key_tables, table);
		key_bindings_unref_table(table);
	}
}