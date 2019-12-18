#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlNs ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_15__ {TYPE_1__* oldNs; } ;
struct TYPE_14__ {scalar_t__ type; struct TYPE_14__* parent; TYPE_1__* ns; TYPE_1__* nsDef; TYPE_3__* doc; } ;
struct TYPE_13__ {int /*<<< orphan*/ * prefix; int /*<<< orphan*/  const* href; struct TYPE_13__* next; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_ENTITY_DECL ; 
 scalar_t__ XML_ENTITY_NODE ; 
 scalar_t__ XML_ENTITY_REF_NODE ; 
 int /*<<< orphan*/  XML_LOCAL_NAMESPACE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  const* XML_XML_NAMESPACE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int xmlNsInScope (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 void* xmlStrdup (int /*<<< orphan*/  const*) ; 
 TYPE_1__* xmlTreeEnsureXMLDecl (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

xmlNsPtr
xmlSearchNsByHref(xmlDocPtr doc, xmlNodePtr node, const xmlChar * href)
{
    xmlNsPtr cur;
    xmlNodePtr orig = node;
    int is_attr;

    if ((node == NULL) || (node->type == XML_NAMESPACE_DECL) || (href == NULL))
        return (NULL);
    if (xmlStrEqual(href, XML_XML_NAMESPACE)) {
        /*
         * Only the document can hold the XML spec namespace.
         */
        if ((doc == NULL) && (node->type == XML_ELEMENT_NODE)) {
            /*
             * The XML-1.0 namespace is normally held on the root
             * element. In this case exceptionally create it on the
             * node element.
             */
            cur = (xmlNsPtr) xmlMalloc(sizeof(xmlNs));
            if (cur == NULL) {
		xmlTreeErrMemory("searching namespace");
                return (NULL);
            }
            memset(cur, 0, sizeof(xmlNs));
            cur->type = XML_LOCAL_NAMESPACE;
            cur->href = xmlStrdup(XML_XML_NAMESPACE);
            cur->prefix = xmlStrdup((const xmlChar *) "xml");
            cur->next = node->nsDef;
            node->nsDef = cur;
            return (cur);
        }
	if (doc == NULL) {
	    doc = node->doc;
	    if (doc == NULL)
		return(NULL);
	}
	/*
	* Return the XML namespace declaration held by the doc.
	*/
	if (doc->oldNs == NULL)
	    return(xmlTreeEnsureXMLDecl(doc));
	else
	    return(doc->oldNs);
    }
    is_attr = (node->type == XML_ATTRIBUTE_NODE);
    while (node != NULL) {
        if ((node->type == XML_ENTITY_REF_NODE) ||
            (node->type == XML_ENTITY_NODE) ||
            (node->type == XML_ENTITY_DECL))
            return (NULL);
        if (node->type == XML_ELEMENT_NODE) {
            cur = node->nsDef;
            while (cur != NULL) {
                if ((cur->href != NULL) && (href != NULL) &&
                    (xmlStrEqual(cur->href, href))) {
		    if (((!is_attr) || (cur->prefix != NULL)) &&
		        (xmlNsInScope(doc, orig, node, cur->prefix) == 1))
			return (cur);
                }
                cur = cur->next;
            }
            if (orig != node) {
                cur = node->ns;
                if (cur != NULL) {
                    if ((cur->href != NULL) && (href != NULL) &&
                        (xmlStrEqual(cur->href, href))) {
			if (((!is_attr) || (cur->prefix != NULL)) &&
		            (xmlNsInScope(doc, orig, node, cur->prefix) == 1))
			    return (cur);
                    }
                }
            }
        }
        node = node->parent;
    }
    return (NULL);
}