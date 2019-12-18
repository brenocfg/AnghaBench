#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  TYPE_2__* xmlDocPtr ;
typedef  TYPE_3__* xmlAttributePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
struct TYPE_12__ {int /*<<< orphan*/  name; TYPE_2__* doc; } ;
struct TYPE_11__ {scalar_t__ atype; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/ * extSubset; int /*<<< orphan*/ * intSubset; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_IDREF ; 
 scalar_t__ XML_ATTRIBUTE_IDREFS ; 
 scalar_t__ XML_HTML_DOCUMENT_NODE ; 
 TYPE_3__* xmlGetDtdAttrDesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xmlIsRef(xmlDocPtr doc, xmlNodePtr elem, xmlAttrPtr attr) {
    if (attr == NULL)
        return(0);
    if (doc == NULL) {
        doc = attr->doc;
	if (doc == NULL) return(0);
    }

    if ((doc->intSubset == NULL) && (doc->extSubset == NULL)) {
        return(0);
    } else if (doc->type == XML_HTML_DOCUMENT_NODE) {
        /* TODO @@@ */
        return(0);
    } else {
        xmlAttributePtr attrDecl;

        if (elem == NULL) return(0);
        attrDecl = xmlGetDtdAttrDesc(doc->intSubset, elem->name, attr->name);
        if ((attrDecl == NULL) && (doc->extSubset != NULL))
            attrDecl = xmlGetDtdAttrDesc(doc->extSubset,
		                         elem->name, attr->name);

	if ((attrDecl != NULL) &&
	    (attrDecl->atype == XML_ATTRIBUTE_IDREF ||
	     attrDecl->atype == XML_ATTRIBUTE_IDREFS))
	return(1);
    }
    return(0);
}