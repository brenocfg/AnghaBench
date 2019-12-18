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
typedef  TYPE_1__* xmlHashTablePtr ;
typedef  struct _xmlHashEntry* xmlHashEntryPtr ;
typedef  int /*<<< orphan*/  xmlHashEntry ;
struct _xmlHashEntry {scalar_t__ valid; struct _xmlHashEntry* next; int /*<<< orphan*/  name3; int /*<<< orphan*/  name2; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int size; struct _xmlHashEntry* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct _xmlHashEntry*,struct _xmlHashEntry*,int) ; 
 int /*<<< orphan*/  memset (struct _xmlHashEntry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlFree (struct _xmlHashEntry*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,int,unsigned long) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 unsigned long xmlHashComputeKey (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct _xmlHashEntry* xmlMalloc (int) ; 

__attribute__((used)) static int
xmlHashGrow(xmlHashTablePtr table, int size) {
    unsigned long key;
    int oldsize, i;
    xmlHashEntryPtr iter, next;
    struct _xmlHashEntry *oldtable;
#ifdef DEBUG_GROW
    unsigned long nbElem = 0;
#endif

    if (table == NULL)
	return(-1);
    if (size < 8)
        return(-1);
    if (size > 8 * 2048)
	return(-1);

    oldsize = table->size;
    oldtable = table->table;
    if (oldtable == NULL)
        return(-1);

    table->table = xmlMalloc(size * sizeof(xmlHashEntry));
    if (table->table == NULL) {
	table->table = oldtable;
	return(-1);
    }
    memset(table->table, 0, size * sizeof(xmlHashEntry));
    table->size = size;

    /*	If the two loops are merged, there would be situations where
	a new entry needs to allocated and data copied into it from
	the main table. So instead, we run through the array twice, first
	copying all the elements in the main array (where we can't get
	conflicts) and then the rest, so we only free (and don't allocate)
    */
    for (i = 0; i < oldsize; i++) {
	if (oldtable[i].valid == 0)
	    continue;
	key = xmlHashComputeKey(table, oldtable[i].name, oldtable[i].name2,
				oldtable[i].name3);
	memcpy(&(table->table[key]), &(oldtable[i]), sizeof(xmlHashEntry));
	table->table[key].next = NULL;
    }

    for (i = 0; i < oldsize; i++) {
	iter = oldtable[i].next;
	while (iter) {
	    next = iter->next;

	    /*
	     * put back the entry in the new table
	     */

	    key = xmlHashComputeKey(table, iter->name, iter->name2,
		                    iter->name3);
	    if (table->table[key].valid == 0) {
		memcpy(&(table->table[key]), iter, sizeof(xmlHashEntry));
		table->table[key].next = NULL;
		xmlFree(iter);
	    } else {
		iter->next = table->table[key].next;
		table->table[key].next = iter;
	    }

#ifdef DEBUG_GROW
	    nbElem++;
#endif

	    iter = next;
	}
    }

    xmlFree(oldtable);

#ifdef DEBUG_GROW
    xmlGenericError(xmlGenericErrorContext,
	    "xmlHashGrow : from %d to %d, %d elems\n", oldsize, size, nbElem);
#endif

    return(0);
}