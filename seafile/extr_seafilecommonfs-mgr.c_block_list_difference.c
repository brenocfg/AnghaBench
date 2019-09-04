#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; } ;
struct TYPE_8__ {int /*<<< orphan*/  n_blocks; TYPE_2__* block_ids; int /*<<< orphan*/  block_hash; } ;
typedef  TYPE_1__ BlockList ;

/* Variables and functions */
 TYPE_1__* block_list_new () ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  g_ptr_array_add (TYPE_2__*,char*) ; 
 char* g_ptr_array_index (TYPE_2__*,int) ; 
 char* g_strdup (char*) ; 

BlockList *
block_list_difference (BlockList *bl1, BlockList *bl2)
{
    BlockList *bl;
    int i;
    char *block_id;
    char *key;

    bl = block_list_new ();

    for (i = 0; i < bl1->block_ids->len; ++i) {
        block_id = g_ptr_array_index (bl1->block_ids, i);
        if (g_hash_table_lookup (bl2->block_hash, block_id) == NULL) {
            key = g_strdup(block_id);
            g_hash_table_replace (bl->block_hash, key, key);
            g_ptr_array_add (bl->block_ids, g_strdup(block_id));
            ++bl->n_blocks;
        }
    }

    return bl;
}