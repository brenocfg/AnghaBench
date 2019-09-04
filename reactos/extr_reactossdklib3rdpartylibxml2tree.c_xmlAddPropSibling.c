#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlAttrPtr ;
struct TYPE_15__ {TYPE_3__* properties; } ;
struct TYPE_14__ {scalar_t__ type; } ;
struct TYPE_13__ {scalar_t__ type; scalar_t__ doc; TYPE_7__* parent; struct TYPE_13__* prev; struct TYPE_13__* next; TYPE_1__* ns; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/ * href; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_DECL ; 
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 TYPE_3__* xmlHasNsProp (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlRemoveProp (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlSetTreeDoc (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static xmlNodePtr
xmlAddPropSibling(xmlNodePtr prev, xmlNodePtr cur, xmlNodePtr prop) {
	xmlAttrPtr attr;

	if ((cur == NULL) || (cur->type != XML_ATTRIBUTE_NODE) ||
	    (prop == NULL) || (prop->type != XML_ATTRIBUTE_NODE) ||
	    ((prev != NULL) && (prev->type != XML_ATTRIBUTE_NODE)))
		return(NULL);

	/* check if an attribute with the same name exists */
	if (prop->ns == NULL)
		attr = xmlHasNsProp(cur->parent, prop->name, NULL);
	else
		attr = xmlHasNsProp(cur->parent, prop->name, prop->ns->href);

	if (prop->doc != cur->doc) {
		xmlSetTreeDoc(prop, cur->doc);
	}
	prop->parent = cur->parent;
	prop->prev = prev;
	if (prev != NULL) {
		prop->next = prev->next;
		prev->next = prop;
		if (prop->next)
			prop->next->prev = prop;
	} else {
		prop->next = cur;
		cur->prev = prop;
	}
	if (prop->prev == NULL && prop->parent != NULL)
		prop->parent->properties = (xmlAttrPtr) prop;
	if ((attr != NULL) && (attr->type != XML_ATTRIBUTE_DECL)) {
		/* different instance, destroy it (attributes must be unique) */
		xmlRemoveProp((xmlAttrPtr) attr);
	}
	return prop;
}