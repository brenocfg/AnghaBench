#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  const* href; int /*<<< orphan*/  const* prefix; } ;

/* Variables and functions */
 TYPE_1__* xmlNewNs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* xmlTreeEnsureXMLDecl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNsPtr
xmlDOMWrapStoreNs(xmlDocPtr doc,
		   const xmlChar *nsName,
		   const xmlChar *prefix)
{
    xmlNsPtr ns;

    if (doc == NULL)
	return (NULL);
    ns = xmlTreeEnsureXMLDecl(doc);
    if (ns == NULL)
	return (NULL);
    if (ns->next != NULL) {
	/* Reuse. */
	ns = ns->next;
	while (ns != NULL) {
	    if (((ns->prefix == prefix) ||
		xmlStrEqual(ns->prefix, prefix)) &&
		xmlStrEqual(ns->href, nsName)) {
		return (ns);
	    }
	    if (ns->next == NULL)
		break;
	    ns = ns->next;
	}
    }
    /* Create. */
    if (ns != NULL) {
        ns->next = xmlNewNs(NULL, nsName, prefix);
        return (ns->next);
    }
    return(NULL);
}