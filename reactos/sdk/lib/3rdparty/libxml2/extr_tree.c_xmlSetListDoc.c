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
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* next; int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  xmlSetTreeDoc (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
xmlSetListDoc(xmlNodePtr list, xmlDocPtr doc) {
    xmlNodePtr cur;

    if ((list == NULL) || (list->type == XML_NAMESPACE_DECL))
	return;
    cur = list;
    while (cur != NULL) {
	if (cur->doc != doc)
	    xmlSetTreeDoc(cur, doc);
	cur = cur->next;
    }
}