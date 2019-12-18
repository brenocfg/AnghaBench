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
struct key_table {int dummy; } ;

/* Variables and functions */
 struct key_table* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct key_table*) ; 
 int /*<<< orphan*/  key_tables ; 

struct key_table *
key_bindings_next_table(struct key_table *table)
{
	return (RB_NEXT(key_tables, &key_tables, table));
}