#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  block_ids; scalar_t__ block_hash; } ;
typedef  TYPE_1__ BlockList ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (scalar_t__) ; 
 int /*<<< orphan*/  g_ptr_array_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
block_list_free (BlockList *bl)
{
    if (bl->block_hash)
        g_hash_table_destroy (bl->block_hash);
    g_ptr_array_free (bl->block_ids, TRUE);
    g_free (bl);
}