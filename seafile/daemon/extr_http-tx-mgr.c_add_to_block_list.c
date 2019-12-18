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
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ g_hash_table_lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 

__attribute__((used)) static void
add_to_block_list (GList **block_list, GHashTable *added_blocks, const char *block_id)
{
    int dummy;

    if (g_hash_table_lookup (added_blocks, block_id))
        return;

    *block_list = g_list_prepend (*block_list, g_strdup(block_id));
    g_hash_table_insert (added_blocks, g_strdup(block_id), &dummy);
}