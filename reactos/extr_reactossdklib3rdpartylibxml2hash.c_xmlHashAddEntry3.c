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
typedef  int /*<<< orphan*/  xmlHashEntry ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_8__ {scalar_t__ valid; struct TYPE_8__* next; void* payload; int /*<<< orphan*/  const* name3; int /*<<< orphan*/  const* name2; int /*<<< orphan*/  const* name; } ;
struct TYPE_7__ {unsigned long size; int /*<<< orphan*/  nbElems; int /*<<< orphan*/ * dict; TYPE_2__* table; } ;

/* Variables and functions */
 unsigned long MAX_HASH_LEN ; 
 int /*<<< orphan*/  const* xmlDictLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xmlDictOwns (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 unsigned long xmlHashComputeKey (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlHashGrow (TYPE_1__*,unsigned long) ; 
 TYPE_2__* xmlMalloc (int) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 void* xmlStrdup (int /*<<< orphan*/  const*) ; 

int
xmlHashAddEntry3(xmlHashTablePtr table, const xmlChar *name,
	         const xmlChar *name2, const xmlChar *name3,
		 void *userdata) {
    unsigned long key, len = 0;
    xmlHashEntryPtr entry;
    xmlHashEntryPtr insert;

    if ((table == NULL) || (name == NULL))
	return(-1);

    /*
     * If using a dict internalize if needed
     */
    if (table->dict) {
        if (!xmlDictOwns(table->dict, name)) {
	    name = xmlDictLookup(table->dict, name, -1);
	    if (name == NULL)
	        return(-1);
	}
        if ((name2 != NULL) && (!xmlDictOwns(table->dict, name2))) {
	    name2 = xmlDictLookup(table->dict, name2, -1);
	    if (name2 == NULL)
	        return(-1);
	}
        if ((name3 != NULL) && (!xmlDictOwns(table->dict, name3))) {
	    name3 = xmlDictLookup(table->dict, name3, -1);
	    if (name3 == NULL)
	        return(-1);
	}
    }

    /*
     * Check for duplicate and insertion location.
     */
    key = xmlHashComputeKey(table, name, name2, name3);
    if (table->table[key].valid == 0) {
	insert = NULL;
    } else {
        if (table->dict) {
	    for (insert = &(table->table[key]); insert->next != NULL;
		 insert = insert->next) {
		if ((insert->name == name) &&
		    (insert->name2 == name2) &&
		    (insert->name3 == name3))
		    return(-1);
		len++;
	    }
	    if ((insert->name == name) &&
		(insert->name2 == name2) &&
		(insert->name3 == name3))
		return(-1);
	} else {
	    for (insert = &(table->table[key]); insert->next != NULL;
		 insert = insert->next) {
		if ((xmlStrEqual(insert->name, name)) &&
		    (xmlStrEqual(insert->name2, name2)) &&
		    (xmlStrEqual(insert->name3, name3)))
		    return(-1);
		len++;
	    }
	    if ((xmlStrEqual(insert->name, name)) &&
		(xmlStrEqual(insert->name2, name2)) &&
		(xmlStrEqual(insert->name3, name3)))
		return(-1);
	}
    }

    if (insert == NULL) {
	entry = &(table->table[key]);
    } else {
	entry = xmlMalloc(sizeof(xmlHashEntry));
	if (entry == NULL)
	     return(-1);
    }

    if (table->dict != NULL) {
        entry->name = (xmlChar *) name;
        entry->name2 = (xmlChar *) name2;
        entry->name3 = (xmlChar *) name3;
    } else {
	entry->name = xmlStrdup(name);
	entry->name2 = xmlStrdup(name2);
	entry->name3 = xmlStrdup(name3);
    }
    entry->payload = userdata;
    entry->next = NULL;
    entry->valid = 1;


    if (insert != NULL)
	insert->next = entry;

    table->nbElems++;

    if (len > MAX_HASH_LEN)
	xmlHashGrow(table, MAX_HASH_LEN * table->size);

    return(0);
}