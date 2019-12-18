#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_13__ {scalar_t__ type; scalar_t__ name; struct TYPE_13__* last; struct TYPE_13__* next; struct TYPE_13__* parent; struct TYPE_13__* prev; int /*<<< orphan*/  doc; int /*<<< orphan*/  content; int /*<<< orphan*/ * children; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XML_TEXT_NODE ; 
 TYPE_1__* xmlAddPropSibling (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlNodeAddContent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlSetTreeDoc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlUnlinkNode (TYPE_1__*) ; 

xmlNodePtr
xmlAddSibling(xmlNodePtr cur, xmlNodePtr elem) {
    xmlNodePtr parent;

    if ((cur == NULL) || (cur->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddSibling : cur == NULL\n");
#endif
	return(NULL);
    }

    if ((elem == NULL) || (elem->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddSibling : elem == NULL\n");
#endif
	return(NULL);
    }

    if (cur == elem) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddSibling : cur == elem\n");
#endif
	return(NULL);
    }

    /*
     * Constant time is we can rely on the ->parent->last to find
     * the last sibling.
     */
    if ((cur->type != XML_ATTRIBUTE_NODE) && (cur->parent != NULL) &&
	(cur->parent->children != NULL) &&
	(cur->parent->last != NULL) &&
	(cur->parent->last->next == NULL)) {
	cur = cur->parent->last;
    } else {
	while (cur->next != NULL) cur = cur->next;
    }

    xmlUnlinkNode(elem);

    if ((cur->type == XML_TEXT_NODE) && (elem->type == XML_TEXT_NODE) &&
        (cur->name == elem->name)) {
	xmlNodeAddContent(cur, elem->content);
	xmlFreeNode(elem);
	return(cur);
    } else if (elem->type == XML_ATTRIBUTE_NODE) {
		return xmlAddPropSibling(cur, cur, elem);
    }

    if (elem->doc != cur->doc) {
	xmlSetTreeDoc(elem, cur->doc);
    }
    parent = cur->parent;
    elem->prev = cur;
    elem->next = NULL;
    elem->parent = parent;
    cur->next = elem;
    if (parent != NULL)
	parent->last = elem;

    return(elem);
}