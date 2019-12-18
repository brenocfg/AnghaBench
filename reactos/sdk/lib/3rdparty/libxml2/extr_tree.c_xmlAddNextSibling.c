#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ name; TYPE_1__* parent; struct TYPE_16__* prev; struct TYPE_16__* next; int /*<<< orphan*/  doc; int /*<<< orphan*/  content; } ;
struct TYPE_15__ {TYPE_2__* last; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XML_TEXT_NODE ; 
 TYPE_2__* xmlAddPropSibling (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlNodeAddContent (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNodeSetContent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlSetTreeDoc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlStrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlUnlinkNode (TYPE_2__*) ; 

xmlNodePtr
xmlAddNextSibling(xmlNodePtr cur, xmlNodePtr elem) {
    if ((cur == NULL) || (cur->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddNextSibling : cur == NULL\n");
#endif
	return(NULL);
    }
    if ((elem == NULL) || (elem->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddNextSibling : elem == NULL\n");
#endif
	return(NULL);
    }

    if (cur == elem) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddNextSibling : cur == elem\n");
#endif
	return(NULL);
    }

    xmlUnlinkNode(elem);

    if (elem->type == XML_TEXT_NODE) {
	if (cur->type == XML_TEXT_NODE) {
	    xmlNodeAddContent(cur, elem->content);
	    xmlFreeNode(elem);
	    return(cur);
	}
	if ((cur->next != NULL) && (cur->next->type == XML_TEXT_NODE) &&
            (cur->name == cur->next->name)) {
	    xmlChar *tmp;

	    tmp = xmlStrdup(elem->content);
	    tmp = xmlStrcat(tmp, cur->next->content);
	    xmlNodeSetContent(cur->next, tmp);
	    xmlFree(tmp);
	    xmlFreeNode(elem);
	    return(cur->next);
	}
    } else if (elem->type == XML_ATTRIBUTE_NODE) {
		return xmlAddPropSibling(cur, cur, elem);
    }

    if (elem->doc != cur->doc) {
	xmlSetTreeDoc(elem, cur->doc);
    }
    elem->parent = cur->parent;
    elem->prev = cur;
    elem->next = cur->next;
    cur->next = elem;
    if (elem->next != NULL)
	elem->next->prev = elem;
    if ((elem->parent != NULL) && (elem->parent->last == cur))
	elem->parent->last = elem;
    return(elem);
}