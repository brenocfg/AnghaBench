#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlDictStringsPtr ;
typedef  TYPE_1__* xmlDictPtr ;
typedef  TYPE_1__* xmlDictEntryPtr ;
struct TYPE_6__ {scalar_t__ ref_counter; size_t size; scalar_t__ nbElems; scalar_t__ valid; struct TYPE_6__* next; struct TYPE_6__* strings; struct TYPE_6__* dict; struct TYPE_6__* subdict; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xmlInitializeDict () ; 
 int /*<<< orphan*/  xmlDictInitialized ; 
 int /*<<< orphan*/  xmlDictMutex ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlRMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlRMutexUnlock (int /*<<< orphan*/ ) ; 

void
xmlDictFree(xmlDictPtr dict) {
    size_t i;
    xmlDictEntryPtr iter;
    xmlDictEntryPtr next;
    int inside_dict = 0;
    xmlDictStringsPtr pool, nextp;

    if (dict == NULL)
	return;

    if (!xmlDictInitialized)
        if (!__xmlInitializeDict())
            return;

    /* decrement the counter, it may be shared by a parser and docs */
    xmlRMutexLock(xmlDictMutex);
    dict->ref_counter--;
    if (dict->ref_counter > 0) {
        xmlRMutexUnlock(xmlDictMutex);
        return;
    }

    xmlRMutexUnlock(xmlDictMutex);

    if (dict->subdict != NULL) {
        xmlDictFree(dict->subdict);
    }

    if (dict->dict) {
	for(i = 0; ((i < dict->size) && (dict->nbElems > 0)); i++) {
	    iter = &(dict->dict[i]);
	    if (iter->valid == 0)
		continue;
	    inside_dict = 1;
	    while (iter) {
		next = iter->next;
		if (!inside_dict)
		    xmlFree(iter);
		dict->nbElems--;
		inside_dict = 0;
		iter = next;
	    }
	}
	xmlFree(dict->dict);
    }
    pool = dict->strings;
    while (pool != NULL) {
        nextp = pool->next;
	xmlFree(pool);
	pool = nextp;
    }
    xmlFree(dict);
}