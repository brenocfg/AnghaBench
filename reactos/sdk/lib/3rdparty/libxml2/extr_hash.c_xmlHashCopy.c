#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlHashTablePtr ;
typedef  TYPE_2__* xmlHashEntryPtr ;
typedef  int /*<<< orphan*/  (* xmlHashCopier ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_8__ {scalar_t__ valid; int /*<<< orphan*/  name; int /*<<< orphan*/  payload; int /*<<< orphan*/  name3; int /*<<< orphan*/  name2; struct TYPE_8__* next; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  nbElems; TYPE_2__* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlHashAddEntry3 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xmlHashCreate (int) ; 

xmlHashTablePtr
xmlHashCopy(xmlHashTablePtr table, xmlHashCopier f) {
    int i;
    xmlHashEntryPtr iter;
    xmlHashEntryPtr next;
    xmlHashTablePtr ret;

    if (table == NULL)
	return(NULL);
    if (f == NULL)
	return(NULL);

    ret = xmlHashCreate(table->size);
    if (ret == NULL)
        return(NULL);

    if (table->table) {
	for(i = 0; i < table->size; i++) {
	    if (table->table[i].valid == 0)
		continue;
	    iter = &(table->table[i]);
	    while (iter) {
		next = iter->next;
		xmlHashAddEntry3(ret, iter->name, iter->name2,
			         iter->name3, f(iter->payload, iter->name));
		iter = next;
	    }
	}
    }
    ret->nbElems = table->nbElems;
    return(ret);
}