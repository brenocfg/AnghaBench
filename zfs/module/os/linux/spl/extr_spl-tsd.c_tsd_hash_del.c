#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_hash_table_t ;
struct TYPE_3__ {int /*<<< orphan*/  he_pid_list; int /*<<< orphan*/  he_key_list; int /*<<< orphan*/  he_list; } ;
typedef  TYPE_1__ tsd_hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tsd_hash_del(tsd_hash_table_t *table, tsd_hash_entry_t *entry)
{
	hlist_del(&entry->he_list);
	list_del_init(&entry->he_key_list);
	list_del_init(&entry->he_pid_list);
}