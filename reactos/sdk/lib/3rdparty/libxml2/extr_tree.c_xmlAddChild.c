#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlAttrPtr ;
struct TYPE_16__ {scalar_t__ type; struct TYPE_16__* prev; struct TYPE_16__* next; } ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ name; scalar_t__ doc; struct TYPE_15__* last; struct TYPE_15__* prev; struct TYPE_15__* next; struct TYPE_15__* children; TYPE_3__* properties; TYPE_1__* ns; int /*<<< orphan*/ * content; struct TYPE_15__* parent; } ;
struct TYPE_14__ {int /*<<< orphan*/ * href; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_DECL ; 
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/  xmlFreeNode (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlFreeProp (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_3__* xmlHasNsProp (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlNodeAddContent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlSetTreeDoc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  xmlUnlinkNode (TYPE_2__*) ; 

xmlNodePtr
xmlAddChild(xmlNodePtr parent, xmlNodePtr cur) {
    xmlNodePtr prev;

    if ((parent == NULL) || (parent->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddChild : parent == NULL\n");
#endif
	return(NULL);
    }

    if ((cur == NULL) || (cur->type == XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddChild : child == NULL\n");
#endif
	return(NULL);
    }

    if (parent == cur) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlAddChild : parent == cur\n");
#endif
	return(NULL);
    }
    /*
     * If cur is a TEXT node, merge its content with adjacent TEXT nodes
     * cur is then freed.
     */
    if (cur->type == XML_TEXT_NODE) {
	if ((parent->type == XML_TEXT_NODE) &&
	    (parent->content != NULL) &&
	    (parent->name == cur->name)) {
	    xmlNodeAddContent(parent, cur->content);
	    xmlFreeNode(cur);
	    return(parent);
	}
	if ((parent->last != NULL) && (parent->last->type == XML_TEXT_NODE) &&
	    (parent->last->name == cur->name) &&
	    (parent->last != cur)) {
	    xmlNodeAddContent(parent->last, cur->content);
	    xmlFreeNode(cur);
	    return(parent->last);
	}
    }

    /*
     * add the new element at the end of the children list.
     */
    prev = cur->parent;
    cur->parent = parent;
    if (cur->doc != parent->doc) {
	xmlSetTreeDoc(cur, parent->doc);
    }
    /* this check prevents a loop on tree-traversions if a developer
     * tries to add a node to its parent multiple times
     */
    if (prev == parent)
	return(cur);

    /*
     * Coalescing
     */
    if ((parent->type == XML_TEXT_NODE) &&
	(parent->content != NULL) &&
	(parent != cur)) {
	xmlNodeAddContent(parent, cur->content);
	xmlFreeNode(cur);
	return(parent);
    }
    if (cur->type == XML_ATTRIBUTE_NODE) {
		if (parent->type != XML_ELEMENT_NODE)
			return(NULL);
	if (parent->properties != NULL) {
	    /* check if an attribute with the same name exists */
	    xmlAttrPtr lastattr;

	    if (cur->ns == NULL)
		lastattr = xmlHasNsProp(parent, cur->name, NULL);
	    else
		lastattr = xmlHasNsProp(parent, cur->name, cur->ns->href);
	    if ((lastattr != NULL) && (lastattr != (xmlAttrPtr) cur) && (lastattr->type != XML_ATTRIBUTE_DECL)) {
		/* different instance, destroy it (attributes must be unique) */
			xmlUnlinkNode((xmlNodePtr) lastattr);
		xmlFreeProp(lastattr);
	    }
		if (lastattr == (xmlAttrPtr) cur)
			return(cur);

	}
	if (parent->properties == NULL) {
	    parent->properties = (xmlAttrPtr) cur;
	} else {
	    /* find the end */
	    xmlAttrPtr lastattr = parent->properties;
	    while (lastattr->next != NULL) {
		lastattr = lastattr->next;
	    }
	    lastattr->next = (xmlAttrPtr) cur;
	    ((xmlAttrPtr) cur)->prev = lastattr;
	}
    } else {
	if (parent->children == NULL) {
	    parent->children = cur;
	    parent->last = cur;
	} else {
	    prev = parent->last;
	    prev->next = cur;
	    cur->prev = prev;
	    parent->last = cur;
	}
    }
    return(cur);
}