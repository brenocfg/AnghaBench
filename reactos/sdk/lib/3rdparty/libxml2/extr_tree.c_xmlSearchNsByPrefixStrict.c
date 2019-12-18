#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_7__ {scalar_t__ type; struct TYPE_7__* parent; TYPE_1__* nsDef; int /*<<< orphan*/ * doc; } ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/ * href; int /*<<< orphan*/  const* prefix; } ;

/* Variables and functions */
 scalar_t__ IS_STR_XML (int /*<<< orphan*/  const*) ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_ENTITY_DECL ; 
 scalar_t__ XML_ENTITY_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* xmlTreeEnsureXMLDecl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlSearchNsByPrefixStrict(xmlDocPtr doc, xmlNodePtr node,
			  const xmlChar* prefix,
			  xmlNsPtr *retNs)
{
    xmlNodePtr cur;
    xmlNsPtr ns;

    if ((doc == NULL) || (node == NULL) || (node->type == XML_NAMESPACE_DECL))
        return(-1);

    if (retNs)
	*retNs = NULL;
    if (IS_STR_XML(prefix)) {
	if (retNs) {
	    *retNs = xmlTreeEnsureXMLDecl(doc);
	    if (*retNs == NULL)
		return (-1);
	}
	return (1);
    }
    cur = node;
    do {
	if (cur->type == XML_ELEMENT_NODE) {
	    if (cur->nsDef != NULL) {
		ns = cur->nsDef;
		do {
		    if ((prefix == ns->prefix) ||
			xmlStrEqual(prefix, ns->prefix))
		    {
			/*
			* Disabled namespaces, e.g. xmlns:abc="".
			*/
			if (ns->href == NULL)
			    return(0);
			if (retNs)
			    *retNs = ns;
			return (1);
		    }
		    ns = ns->next;
		} while (ns != NULL);
	    }
	} else if ((cur->type == XML_ENTITY_NODE) ||
            (cur->type == XML_ENTITY_DECL))
	    return (0);
	cur = cur->parent;
    } while ((cur != NULL) && (cur->doc != (xmlDocPtr) cur));
    return (0);
}