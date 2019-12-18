#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ name; struct TYPE_8__* last; int /*<<< orphan*/ * doc; struct TYPE_8__* parent; struct TYPE_8__* next; struct TYPE_8__* prev; int /*<<< orphan*/  content; struct TYPE_8__* children; } ;

/* Variables and functions */
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlNodeAddContent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSetTreeDoc (TYPE_1__*,int /*<<< orphan*/ *) ; 

xmlNodePtr
xmlAddChildList(xmlNodePtr parent, xmlNodePtr cur) {
    xmlNodePtr prev;

    if ((parent == NULL) || (parent->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddChildList : parent == NULL\n");
#endif
	return(NULL);
    }

    if ((cur == NULL) || (cur->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddChildList : child == NULL\n");
#endif
	return(NULL);
    }

    if ((cur->doc != NULL) && (parent->doc != NULL) &&
        (cur->doc != parent->doc)) {
#ifdef DEBUG_TREE
	xmlGenericError(xmlGenericErrorContext,
		"Elements moved to a different document\n");
#endif
    }

    /*
     * add the first element at the end of the children list.
     */

    if (parent->children == NULL) {
        parent->children = cur;
    } else {
	/*
	 * If cur and parent->last both are TEXT nodes, then merge them.
	 */
	if ((cur->type == XML_TEXT_NODE) &&
	    (parent->last->type == XML_TEXT_NODE) &&
	    (cur->name == parent->last->name)) {
	    xmlNodeAddContent(parent->last, cur->content);
	    /*
	     * if it's the only child, nothing more to be done.
	     */
	    if (cur->next == NULL) {
		xmlFreeNode(cur);
		return(parent->last);
	    }
	    prev = cur;
	    cur = cur->next;
	    xmlFreeNode(prev);
	}
        prev = parent->last;
	prev->next = cur;
	cur->prev = prev;
    }
    while (cur->next != NULL) {
	cur->parent = parent;
	if (cur->doc != parent->doc) {
	    xmlSetTreeDoc(cur, parent->doc);
	}
        cur = cur->next;
    }
    cur->parent = parent;
    /* the parent may not be linked to a doc ! */
    if (cur->doc != parent->doc) {
        xmlSetTreeDoc(cur, parent->doc);
    }
    parent->last = cur;

    return(cur);
}