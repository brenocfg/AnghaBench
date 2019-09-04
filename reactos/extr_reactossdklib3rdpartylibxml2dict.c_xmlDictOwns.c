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
typedef  TYPE_1__* xmlDictStringsPtr ;
typedef  TYPE_2__* xmlDictPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {struct TYPE_5__* subdict; TYPE_1__* strings; } ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  const* free; int /*<<< orphan*/  const* array; } ;

/* Variables and functions */

int
xmlDictOwns(xmlDictPtr dict, const xmlChar *str) {
    xmlDictStringsPtr pool;

    if ((dict == NULL) || (str == NULL))
	return(-1);
    pool = dict->strings;
    while (pool != NULL) {
        if ((str >= &pool->array[0]) && (str <= pool->free))
	    return(1);
	pool = pool->next;
    }
    if (dict->subdict)
        return(xmlDictOwns(dict->subdict, str));
    return(0);
}