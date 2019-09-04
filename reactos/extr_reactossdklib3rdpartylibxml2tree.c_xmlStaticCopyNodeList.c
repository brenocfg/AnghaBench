#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
struct TYPE_8__ {struct TYPE_8__* next; struct TYPE_8__* prev; } ;

/* Variables and functions */
 TYPE_1__* xmlStaticCopyNode (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static xmlNodePtr
xmlStaticCopyNodeList(xmlNodePtr node, xmlDocPtr doc, xmlNodePtr parent) {
    xmlNodePtr ret = NULL;
    xmlNodePtr p = NULL,q;

    while (node != NULL) {
#ifdef LIBXML_TREE_ENABLED
	if (node->type == XML_DTD_NODE ) {
	    if (doc == NULL) {
		node = node->next;
		continue;
	    }
	    if (doc->intSubset == NULL) {
		q = (xmlNodePtr) xmlCopyDtd( (xmlDtdPtr) node );
		if (q == NULL) return(NULL);
		q->doc = doc;
		q->parent = parent;
		doc->intSubset = (xmlDtdPtr) q;
		xmlAddChild(parent, q);
	    } else {
		q = (xmlNodePtr) doc->intSubset;
		xmlAddChild(parent, q);
	    }
	} else
#endif /* LIBXML_TREE_ENABLED */
	    q = xmlStaticCopyNode(node, doc, parent, 1);
	if (q == NULL) return(NULL);
	if (ret == NULL) {
	    q->prev = NULL;
	    ret = p = q;
	} else if (p != q) {
	/* the test is required if xmlStaticCopyNode coalesced 2 text nodes */
	    p->next = q;
	    q->prev = p;
	    p = q;
	}
	node = node->next;
    }
    return(ret);
}