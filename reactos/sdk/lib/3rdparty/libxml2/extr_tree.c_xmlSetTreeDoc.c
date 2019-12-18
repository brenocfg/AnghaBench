#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  void* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_2__* xmlAttrPtr ;
struct TYPE_9__ {scalar_t__ atype; struct TYPE_9__* next; int /*<<< orphan*/ * children; void* doc; } ;
struct TYPE_8__ {scalar_t__ type; void* doc; int /*<<< orphan*/ * children; TYPE_2__* properties; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_ID ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  xmlAddID (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ xmlIsID (void*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * xmlNodeListGetString (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmlRemoveID (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlSetListDoc (int /*<<< orphan*/ *,void*) ; 

void
xmlSetTreeDoc(xmlNodePtr tree, xmlDocPtr doc) {
    xmlAttrPtr prop;

    if ((tree == NULL) || (tree->type == XML_NAMESPACE_DECL))
	return;
    if (tree->doc != doc) {
	if(tree->type == XML_ELEMENT_NODE) {
	    prop = tree->properties;
	    while (prop != NULL) {
                if (prop->atype == XML_ATTRIBUTE_ID) {
                    xmlRemoveID(tree->doc, prop);
                }

		prop->doc = doc;
		xmlSetListDoc(prop->children, doc);

                /*
                 * TODO: ID attributes should be also added to the new
                 * document, but this breaks things like xmlReplaceNode.
                 * The underlying problem is that xmlRemoveID is only called
                 * if a node is destroyed, not if it's unlinked.
                 */
#if 0
                if (xmlIsID(doc, tree, prop)) {
                    xmlChar *idVal = xmlNodeListGetString(doc, prop->children,
                                                          1);
                    xmlAddID(NULL, doc, idVal, prop);
                }
#endif

		prop = prop->next;
	    }
	}
	if (tree->children != NULL)
	    xmlSetListDoc(tree->children, doc);
	tree->doc = doc;
    }
}