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
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {scalar_t__ type; struct TYPE_9__* parent; TYPE_1__* nsDef; int /*<<< orphan*/ * doc; } ;
struct TYPE_8__ {int /*<<< orphan*/  const* prefix; int /*<<< orphan*/  const* href; struct TYPE_8__* next; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_ENTITY_DECL ; 
 scalar_t__ XML_ENTITY_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  const* XML_XML_NAMESPACE ; 
 int xmlNsInScope (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* xmlTreeEnsureXMLDecl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xmlSearchNsByNamespaceStrict(xmlDocPtr doc, xmlNodePtr node,
			     const xmlChar* nsName,
			     xmlNsPtr *retNs, int prefixed)
{
    xmlNodePtr cur, prev = NULL, out = NULL;
    xmlNsPtr ns, prevns;

    if ((doc == NULL) || (nsName == NULL) || (retNs == NULL))
	return (-1);
    if ((node == NULL) || (node->type == XML_NAMESPACE_DECL))
        return(-1);

    *retNs = NULL;
    if (xmlStrEqual(nsName, XML_XML_NAMESPACE)) {
	*retNs = xmlTreeEnsureXMLDecl(doc);
	if (*retNs == NULL)
	    return (-1);
	return (1);
    }
    cur = node;
    do {
	if (cur->type == XML_ELEMENT_NODE) {
	    if (cur->nsDef != NULL) {
		for (ns = cur->nsDef; ns != NULL; ns = ns->next) {
		    if (prefixed && (ns->prefix == NULL))
			continue;
		    if (prev != NULL) {
			/*
			* Check the last level of ns-decls for a
			* shadowing prefix.
			*/
			prevns = prev->nsDef;
			do {
			    if ((prevns->prefix == ns->prefix) ||
				((prevns->prefix != NULL) &&
				(ns->prefix != NULL) &&
				xmlStrEqual(prevns->prefix, ns->prefix))) {
				/*
				* Shadowed.
				*/
				break;
			    }
			    prevns = prevns->next;
			} while (prevns != NULL);
			if (prevns != NULL)
			    continue;
		    }
		    /*
		    * Ns-name comparison.
		    */
		    if ((nsName == ns->href) ||
			xmlStrEqual(nsName, ns->href)) {
			/*
			* At this point the prefix can only be shadowed,
			* if we are the the (at least) 3rd level of
			* ns-decls.
			*/
			if (out) {
			    int ret;

			    ret = xmlNsInScope(doc, node, prev, ns->prefix);
			    if (ret < 0)
				return (-1);
			    /*
			    * TODO: Should we try to find a matching ns-name
			    * only once? This here keeps on searching.
			    * I think we should try further since, there might
			    * be an other matching ns-decl with an unshadowed
			    * prefix.
			    */
			    if (! ret)
				continue;
			}
			*retNs = ns;
			return (1);
		    }
		}
		out = prev;
		prev = cur;
	    }
	} else if ((cur->type == XML_ENTITY_NODE) ||
            (cur->type == XML_ENTITY_DECL))
	    return (0);
	cur = cur->parent;
    } while ((cur != NULL) && (cur->doc != (xmlDocPtr) cur));
    return (0);
}