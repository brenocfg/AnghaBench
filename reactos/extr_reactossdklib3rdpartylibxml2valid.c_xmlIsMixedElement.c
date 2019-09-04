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
typedef  TYPE_1__* xmlElementPtr ;
typedef  TYPE_2__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_6__ {int /*<<< orphan*/ * extSubset; int /*<<< orphan*/ * intSubset; } ;
struct TYPE_5__ {int etype; } ;

/* Variables and functions */
#define  XML_ELEMENT_TYPE_ANY 132 
#define  XML_ELEMENT_TYPE_ELEMENT 131 
#define  XML_ELEMENT_TYPE_EMPTY 130 
#define  XML_ELEMENT_TYPE_MIXED 129 
#define  XML_ELEMENT_TYPE_UNDEFINED 128 
 TYPE_1__* xmlGetDtdElementDesc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int
xmlIsMixedElement(xmlDocPtr doc, const xmlChar *name) {
    xmlElementPtr elemDecl;

    if ((doc == NULL) || (doc->intSubset == NULL)) return(-1);

    elemDecl = xmlGetDtdElementDesc(doc->intSubset, name);
    if ((elemDecl == NULL) && (doc->extSubset != NULL))
	elemDecl = xmlGetDtdElementDesc(doc->extSubset, name);
    if (elemDecl == NULL) return(-1);
    switch (elemDecl->etype) {
	case XML_ELEMENT_TYPE_UNDEFINED:
	    return(-1);
	case XML_ELEMENT_TYPE_ELEMENT:
	    return(0);
        case XML_ELEMENT_TYPE_EMPTY:
	    /*
	     * return 1 for EMPTY since we want VC error to pop up
	     * on <empty>     </empty> for example
	     */
	case XML_ELEMENT_TYPE_ANY:
	case XML_ELEMENT_TYPE_MIXED:
	    return(1);
    }
    return(1);
}