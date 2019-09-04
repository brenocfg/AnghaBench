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
struct hash_table {scalar_t__ nr; scalar_t__ size; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void free_hash(struct hash_table *table)
{
    free(table->array);
    table->array = NULL;
    table->size = 0;
    table->nr = 0;
}