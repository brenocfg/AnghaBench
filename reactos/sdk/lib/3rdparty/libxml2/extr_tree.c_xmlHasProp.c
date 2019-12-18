#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  name; TYPE_2__* doc; TYPE_4__* properties; } ;
typedef  TYPE_1__ xmlNode ;
typedef  TYPE_2__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_3__* xmlAttributePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
struct TYPE_11__ {struct TYPE_11__* next; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/ * defaultValue; } ;
struct TYPE_9__ {int /*<<< orphan*/ * extSubset; int /*<<< orphan*/ * intSubset; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  xmlCheckDTD ; 
 TYPE_3__* xmlGetDtdAttrDesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

xmlAttrPtr
xmlHasProp(const xmlNode *node, const xmlChar *name) {
    xmlAttrPtr prop;
    xmlDocPtr doc;

    if ((node == NULL) || (node->type != XML_ELEMENT_NODE) || (name == NULL))
        return(NULL);
    /*
     * Check on the properties attached to the node
     */
    prop = node->properties;
    while (prop != NULL) {
        if (xmlStrEqual(prop->name, name))  {
	    return(prop);
        }
	prop = prop->next;
    }
    if (!xmlCheckDTD) return(NULL);

    /*
     * Check if there is a default declaration in the internal
     * or external subsets
     */
    doc =  node->doc;
    if (doc != NULL) {
        xmlAttributePtr attrDecl;
        if (doc->intSubset != NULL) {
	    attrDecl = xmlGetDtdAttrDesc(doc->intSubset, node->name, name);
	    if ((attrDecl == NULL) && (doc->extSubset != NULL))
		attrDecl = xmlGetDtdAttrDesc(doc->extSubset, node->name, name);
            if ((attrDecl != NULL) && (attrDecl->defaultValue != NULL))
              /* return attribute declaration only if a default value is given
                 (that includes #FIXED declarations) */
		return((xmlAttrPtr) attrDecl);
	}
    }
    return(NULL);
}