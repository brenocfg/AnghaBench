#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_1__* xmlAttributePtr ;
struct TYPE_6__ {scalar_t__ type; TYPE_3__* children; int /*<<< orphan*/  doc; } ;
typedef  TYPE_2__ xmlAttr ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/ * content; int /*<<< orphan*/ * next; } ;
struct TYPE_5__ {int /*<<< orphan*/ * defaultValue; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_DECL ; 
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 int /*<<< orphan*/ * xmlNodeListGetString (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlChar*
xmlGetPropNodeValueInternal(const xmlAttr *prop)
{
    if (prop == NULL)
	return(NULL);
    if (prop->type == XML_ATTRIBUTE_NODE) {
	/*
	* Note that we return at least the empty string.
	*   TODO: Do we really always want that?
	*/
	if (prop->children != NULL) {
	    if ((prop->children->next == NULL) &&
		((prop->children->type == XML_TEXT_NODE) ||
		(prop->children->type == XML_CDATA_SECTION_NODE)))
	    {
		/*
		* Optimization for the common case: only 1 text node.
		*/
		return(xmlStrdup(prop->children->content));
	    } else {
		xmlChar *ret;

		ret = xmlNodeListGetString(prop->doc, prop->children, 1);
		if (ret != NULL)
		    return(ret);
	    }
	}
	return(xmlStrdup((xmlChar *)""));
    } else if (prop->type == XML_ATTRIBUTE_DECL) {
	return(xmlStrdup(((xmlAttributePtr)prop)->defaultValue));
    }
    return(NULL);
}