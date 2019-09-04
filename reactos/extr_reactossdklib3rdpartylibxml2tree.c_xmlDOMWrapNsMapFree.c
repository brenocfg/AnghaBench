#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsMapPtr ;
typedef  TYPE_1__* xmlNsMapItemPtr ;
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* first; struct TYPE_5__* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 

__attribute__((used)) static void
xmlDOMWrapNsMapFree(xmlNsMapPtr nsmap)
{
    xmlNsMapItemPtr cur, tmp;

    if (nsmap == NULL)
	return;
    cur = nsmap->pool;
    while (cur != NULL) {
	tmp = cur;
	cur = cur->next;
	xmlFree(tmp);
    }
    cur = nsmap->first;
    while (cur != NULL) {
	tmp = cur;
	cur = cur->next;
	xmlFree(tmp);
    }
    xmlFree(nsmap);
}