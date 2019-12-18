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
struct index_state {int /*<<< orphan*/  i_name_hash; int /*<<< orphan*/  name_hash; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cache_entry*) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_utf8_strdown (int /*<<< orphan*/ ,int) ; 

void add_name_hash(struct index_state *istate, struct cache_entry *ce)
{
    g_hash_table_insert (istate->name_hash, g_strdup(ce->name), ce);
#if defined WIN32 || defined __APPLE__
    g_hash_table_insert (istate->i_name_hash, g_utf8_strdown(ce->name, -1), ce);
#endif
}