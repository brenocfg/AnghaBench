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
struct key_table {int /*<<< orphan*/  key_bindings; } ;
struct key_binding {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  key_code ;

/* Variables and functions */
 struct key_binding* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key_binding*) ; 
 int /*<<< orphan*/  key_bindings ; 

struct key_binding *
key_bindings_get(struct key_table *table, key_code key)
{
	struct key_binding	bd;

	bd.key = key;
	return (RB_FIND(key_bindings, &table->key_bindings, &bd));
}