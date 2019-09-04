#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; TYPE_2__* table; scalar_t__ filled; } ;
typedef  TYPE_1__ htab_table ;
struct TYPE_5__ {struct TYPE_5__* str; scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  safe_free (TYPE_2__*) ; 

void htab_destroy(htab_table* htab)
{
	size_t i;

	if ((htab == NULL) || (htab->table == NULL)) {
		return;
	}

	for (i=0; i<htab->size+1; i++) {
		if (htab->table[i].used) {
			safe_free(htab->table[i].str);
		}
	}
	htab->filled = 0; htab->size = 0;
	safe_free(htab->table);
	htab->table = NULL;
}