#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_11__ {int type; int /*<<< orphan*/ * content; int /*<<< orphan*/ * nsDef; int /*<<< orphan*/ * properties; TYPE_1__* doc; struct TYPE_11__* next; struct TYPE_11__* last; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dict; } ;

/* Variables and functions */
#define  XML_ATTRIBUTE_DECL 148 
#define  XML_ATTRIBUTE_NODE 147 
#define  XML_CDATA_SECTION_NODE 146 
#define  XML_COMMENT_NODE 145 
#define  XML_DOCB_DOCUMENT_NODE 144 
#define  XML_DOCUMENT_FRAG_NODE 143 
#define  XML_DOCUMENT_NODE 142 
#define  XML_DOCUMENT_TYPE_NODE 141 
#define  XML_DTD_NODE 140 
#define  XML_ELEMENT_DECL 139 
#define  XML_ELEMENT_NODE 138 
#define  XML_ENTITY_DECL 137 
#define  XML_ENTITY_NODE 136 
#define  XML_ENTITY_REF_NODE 135 
#define  XML_HTML_DOCUMENT_NODE 134 
#define  XML_NAMESPACE_DECL 133 
#define  XML_NOTATION_NODE 132 
#define  XML_PI_NODE 131 
#define  XML_TEXT_NODE 130 
#define  XML_XINCLUDE_END 129 
#define  XML_XINCLUDE_START 128 
 TYPE_2__* xmlAddChild (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlDictOwns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_2__* xmlNewTextLen (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xmlStrncat (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xmlStrncatNew (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xmlTextMerge (TYPE_2__*,TYPE_2__*) ; 

void
xmlNodeAddContentLen(xmlNodePtr cur, const xmlChar *content, int len) {
    if (cur == NULL) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"xmlNodeAddContentLen : node == NULL\n");
#endif
	return;
    }
    if (len <= 0) return;
    switch (cur->type) {
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE: {
	    xmlNodePtr last, newNode, tmp;

	    last = cur->last;
	    newNode = xmlNewTextLen(content, len);
	    if (newNode != NULL) {
		tmp = xmlAddChild(cur, newNode);
		if (tmp != newNode)
		    return;
	        if ((last != NULL) && (last->next == newNode)) {
		    xmlTextMerge(last, newNode);
		}
	    }
	    break;
	}
        case XML_ATTRIBUTE_NODE:
	    break;
        case XML_TEXT_NODE:
        case XML_CDATA_SECTION_NODE:
        case XML_ENTITY_REF_NODE:
        case XML_ENTITY_NODE:
        case XML_PI_NODE:
        case XML_COMMENT_NODE:
        case XML_NOTATION_NODE:
	    if (content != NULL) {
	        if ((cur->content == (xmlChar *) &(cur->properties)) ||
		    ((cur->doc != NULL) && (cur->doc->dict != NULL) &&
			    xmlDictOwns(cur->doc->dict, cur->content))) {
		    cur->content = xmlStrncatNew(cur->content, content, len);
		    cur->properties = NULL;
		    cur->nsDef = NULL;
		    break;
		}
		cur->content = xmlStrncat(cur->content, content, len);
            }
        case XML_DOCUMENT_NODE:
        case XML_DTD_NODE:
        case XML_HTML_DOCUMENT_NODE:
        case XML_DOCUMENT_TYPE_NODE:
	case XML_NAMESPACE_DECL:
	case XML_XINCLUDE_START:
	case XML_XINCLUDE_END:
#ifdef LIBXML_DOCB_ENABLED
	case XML_DOCB_DOCUMENT_NODE:
#endif
	    break;
        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
	    break;
    }
}