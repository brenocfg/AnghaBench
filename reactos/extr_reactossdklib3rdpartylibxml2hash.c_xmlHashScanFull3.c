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
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {scalar_t__ valid; int /*<<< orphan*/  name3; int /*<<< orphan*/  name2; int /*<<< orphan*/  name; int /*<<< orphan*/ * payload; struct TYPE_5__* next; } ;
struct TYPE_4__ {int size; TYPE_2__* table; } ;

/* Variables and functions */
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void
xmlHashScanFull3(xmlHashTablePtr table, const xmlChar *name,
		 const xmlChar *name2, const xmlChar *name3,
		 xmlHashScannerFull f, void *data) {
    int i;
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
		if (((name == NULL) || (xmlStrEqual(name, iter->name))) &&
		    ((name2 == NULL) || (xmlStrEqual(name2, iter->name2))) &&
		    ((name3 == NULL) || (xmlStrEqual(name3, iter->name3))) &&
		    (iter->payload != NULL)) {
		    f(iter->payload, data, iter->name,
		      iter->name2, iter->name3);
		}
		iter = next;
	    }
	}
    }
}