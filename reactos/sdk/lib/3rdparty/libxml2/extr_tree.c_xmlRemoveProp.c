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
typedef  TYPE_2__* xmlAttrPtr ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; TYPE_1__* parent; } ;
struct TYPE_5__ {TYPE_2__* properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFreeProp (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

int
xmlRemoveProp(xmlAttrPtr cur) {
    xmlAttrPtr tmp;
    if (cur == NULL) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlRemoveProp : cur == NULL\n");
#endif
	return(-1);
    }
    if (cur->parent == NULL) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlRemoveProp : cur->parent == NULL\n");
#endif
	return(-1);
    }
    tmp = cur->parent->properties;
    if (tmp == cur) {
        cur->parent->properties = cur->next;
		if (cur->next != NULL)
			cur->next->prev = NULL;
	xmlFreeProp(cur);
	return(0);
    }
    while (tmp != NULL) {
	if (tmp->next == cur) {
	    tmp->next = cur->next;
	    if (tmp->next != NULL)
		tmp->next->prev = tmp;
	    xmlFreeProp(cur);
	    return(0);
	}
        tmp = tmp->next;
    }
#ifdef DEBUG_TREE
    xmlGenericError(xmlGenericErrorContext,
	    "xmlRemoveProp : attribute not owned by its node\n");
#endif
    return(-1);
}