#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  TYPE_2__* xmlAttrPtr ;
struct TYPE_10__ {struct TYPE_10__* next; struct TYPE_10__* prev; } ;
struct TYPE_9__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 TYPE_2__* xmlCopyProp (TYPE_1__*,TYPE_2__*) ; 

xmlAttrPtr
xmlCopyPropList(xmlNodePtr target, xmlAttrPtr cur) {
    xmlAttrPtr ret = NULL;
    xmlAttrPtr p = NULL,q;

    if ((target != NULL) && (target->type != XML_ELEMENT_NODE))
        return(NULL);
    while (cur != NULL) {
        q = xmlCopyProp(target, cur);
	if (q == NULL)
	    return(NULL);
	if (p == NULL) {
	    ret = p = q;
	} else {
	    p->next = q;
	    q->prev = p;
	    p = q;
	}
	cur = cur->next;
    }
    return(ret);
}