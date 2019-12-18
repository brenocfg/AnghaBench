#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  prefix ;
struct TYPE_13__ {scalar_t__ type; } ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  href; int /*<<< orphan*/ * prefix; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_1__* xmlNewNs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* xmlSearchNsByHref (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlNsPtr
xmlNewReconciliedNs(xmlDocPtr doc, xmlNodePtr tree, xmlNsPtr ns) {
    xmlNsPtr def;
    xmlChar prefix[50];
    int counter = 1;

    if ((tree == NULL) || (tree->type != XML_ELEMENT_NODE)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlNewReconciliedNs : tree == NULL\n");
#endif
	return(NULL);
    }
    if ((ns == NULL) || (ns->type != XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlNewReconciliedNs : ns == NULL\n");
#endif
	return(NULL);
    }
    /*
     * Search an existing namespace definition inherited.
     */
    def = xmlSearchNsByHref(doc, tree, ns->href);
    if (def != NULL)
        return(def);

    /*
     * Find a close prefix which is not already in use.
     * Let's strip namespace prefixes longer than 20 chars !
     */
    if (ns->prefix == NULL)
	snprintf((char *) prefix, sizeof(prefix), "default");
    else
	snprintf((char *) prefix, sizeof(prefix), "%.20s", (char *)ns->prefix);

    def = xmlSearchNs(doc, tree, prefix);
    while (def != NULL) {
        if (counter > 1000) return(NULL);
	if (ns->prefix == NULL)
	    snprintf((char *) prefix, sizeof(prefix), "default%d", counter++);
	else
	    snprintf((char *) prefix, sizeof(prefix), "%.20s%d",
		(char *)ns->prefix, counter++);
	def = xmlSearchNs(doc, tree, prefix);
    }

    /*
     * OK, now we are ready to create a new one.
     */
    def = xmlNewNs(tree, ns->href, prefix);
    return(def);
}