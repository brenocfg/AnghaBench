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
struct TYPE_3__ {int /*<<< orphan*/  n_blocks; int /*<<< orphan*/  block_ids; int /*<<< orphan*/  block_hash; } ;
typedef  TYPE_1__ BlockList ;

/* Variables and functions */
 scalar_t__ g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ ,char*) ; 
 char* g_strdup (char const*) ; 

void
block_list_insert (BlockList *bl, const char *block_id)
{
    if (g_hash_table_lookup (bl->block_hash, block_id))
        return;

    char *key = g_strdup(block_id);
    g_hash_table_replace (bl->block_hash, key, key);
    g_ptr_array_add (bl->block_ids, g_strdup(block_id));
    ++bl->n_blocks;
}