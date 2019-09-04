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
typedef  TYPE_1__* xmlHashTablePtr ;
typedef  int /*<<< orphan*/  (* xmlHashScannerFull ) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_2__* xmlHashEntryPtr ;
struct TYPE_5__ {scalar_t__ valid; struct TYPE_5__* next; int /*<<< orphan*/  name3; int /*<<< orphan*/  name2; int /*<<< orphan*/  name; int /*<<< orphan*/ * payload; } ;
struct TYPE_4__ {int size; int nbElems; TYPE_2__* table; } ;

/* Variables and functions */

void
xmlHashScanFull(xmlHashTablePtr table, xmlHashScannerFull f, void *data) {
    int i, nb;
    xmlHashEntryPtr iter;
    xmlHashEntryPtr next;

    if (table == NULL)
	return;
    if (f == NULL)
	return;

    if (table->table) {
	for(i = 0; i < table->size; i++) {
	    if (table->table[i].valid == 0)
		continue;
	    iter = &(table->table[i]);
	    while (iter) {
		next = iter->next;
                nb = table->nbElems;
		if ((f != NULL) && (iter->payload != NULL))
		    f(iter->payload, data, iter->name,
		      iter->name2, iter->name3);
                if (nb != table->nbElems) {
                    /* table was modified by the callback, be careful */
                    if (iter == &(table->table[i])) {
                        if (table->table[i].valid == 0)
                            iter = NULL;
                        if (table->table[i].next != next)
			    iter = &(table->table[i]);
                    } else
		        iter = next;
                } else
		    iter = next;
	    }
	}
    }
}