#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlHashTablePtr ;
typedef  TYPE_2__* xmlHashEntryPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_6__ {scalar_t__ valid; void* payload; int /*<<< orphan*/  const* name3; int /*<<< orphan*/  const* name2; int /*<<< orphan*/  const* name; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* table; scalar_t__ dict; } ;

/* Variables and functions */
 unsigned long xmlHashComputeKey (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void *
xmlHashLookup3(xmlHashTablePtr table, const xmlChar *name,
	       const xmlChar *name2, const xmlChar *name3) {
    unsigned long key;
    xmlHashEntryPtr entry;

    if (table == NULL)
	return(NULL);
    if (name == NULL)
	return(NULL);
    key = xmlHashComputeKey(table, name, name2, name3);
    if (table->table[key].valid == 0)
	return(NULL);
    if (table->dict) {
	for (entry = &(table->table[key]); entry != NULL; entry = entry->next) {
	    if ((entry->name == name) &&
		(entry->name2 == name2) &&
		(entry->name3 == name3))
		return(entry->payload);
	}
    }
    for (entry = &(table->table[key]); entry != NULL; entry = entry->next) {
	if ((xmlStrEqual(entry->name, name)) &&
	    (xmlStrEqual(entry->name2, name2)) &&
	    (xmlStrEqual(entry->name3, name3)))
	    return(entry->payload);
    }
    return(NULL);
}