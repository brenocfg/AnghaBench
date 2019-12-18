#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_9__ {int type; struct TYPE_9__* next; struct TYPE_9__* children; int /*<<< orphan*/  name; int /*<<< orphan*/  doc; int /*<<< orphan*/ * content; struct TYPE_9__* parent; } ;
typedef  TYPE_2__ xmlNode ;
typedef  TYPE_4__* xmlEntityPtr ;
typedef  int /*<<< orphan*/ * xmlBufPtr ;
typedef  TYPE_5__* xmlAttrPtr ;
struct TYPE_11__ {TYPE_2__* children; } ;
struct TYPE_10__ {TYPE_2__* children; } ;
struct TYPE_8__ {int /*<<< orphan*/ * href; } ;

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
 int /*<<< orphan*/  xmlBufCat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* xmlGetDocEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xmlBufGetNodeContent(xmlBufPtr buf, const xmlNode *cur)
{
    if ((cur == NULL) || (buf == NULL)) return(-1);
    switch (cur->type) {
        case XML_CDATA_SECTION_NODE:
        case XML_TEXT_NODE:
	    xmlBufCat(buf, cur->content);
            break;
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE:{
                const xmlNode *tmp = cur;

                while (tmp != NULL) {
                    switch (tmp->type) {
                        case XML_CDATA_SECTION_NODE:
                        case XML_TEXT_NODE:
                            if (tmp->content != NULL)
                                xmlBufCat(buf, tmp->content);
                            break;
                        case XML_ENTITY_REF_NODE:
                            xmlBufGetNodeContent(buf, tmp);
                            break;
                        default:
                            break;
                    }
                    /*
                     * Skip to next node
                     */
                    if (tmp->children != NULL) {
                        if (tmp->children->type != XML_ENTITY_DECL) {
                            tmp = tmp->children;
                            continue;
                        }
                    }
                    if (tmp == cur)
                        break;

                    if (tmp->next != NULL) {
                        tmp = tmp->next;
                        continue;
                    }

                    do {
                        tmp = tmp->parent;
                        if (tmp == NULL)
                            break;
                        if (tmp == cur) {
                            tmp = NULL;
                            break;
                        }
                        if (tmp->next != NULL) {
                            tmp = tmp->next;
                            break;
                        }
                    } while (tmp != NULL);
                }
		break;
            }
        case XML_ATTRIBUTE_NODE:{
                xmlAttrPtr attr = (xmlAttrPtr) cur;
		xmlNodePtr tmp = attr->children;

		while (tmp != NULL) {
		    if (tmp->type == XML_TEXT_NODE)
		        xmlBufCat(buf, tmp->content);
		    else
		        xmlBufGetNodeContent(buf, tmp);
		    tmp = tmp->next;
		}
                break;
            }
        case XML_COMMENT_NODE:
        case XML_PI_NODE:
	    xmlBufCat(buf, cur->content);
            break;
        case XML_ENTITY_REF_NODE:{
                xmlEntityPtr ent;
                xmlNodePtr tmp;

                /* lookup entity declaration */
                ent = xmlGetDocEntity(cur->doc, cur->name);
                if (ent == NULL)
                    return(-1);

                /* an entity content can be any "well balanced chunk",
                 * i.e. the result of the content [43] production:
                 * http://www.w3.org/TR/REC-xml#NT-content
                 * -> we iterate through child nodes and recursive call
                 * xmlNodeGetContent() which handles all possible node types */
                tmp = ent->children;
                while (tmp) {
		    xmlBufGetNodeContent(buf, tmp);
                    tmp = tmp->next;
                }
		break;
            }
        case XML_ENTITY_NODE:
        case XML_DOCUMENT_TYPE_NODE:
        case XML_NOTATION_NODE:
        case XML_DTD_NODE:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
            break;
        case XML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
        case XML_HTML_DOCUMENT_NODE:
	    cur = cur->children;
	    while (cur!= NULL) {
		if ((cur->type == XML_ELEMENT_NODE) ||
		    (cur->type == XML_TEXT_NODE) ||
		    (cur->type == XML_CDATA_SECTION_NODE)) {
		    xmlBufGetNodeContent(buf, cur);
		}
		cur = cur->next;
	    }
	    break;
        case XML_NAMESPACE_DECL:
	    xmlBufCat(buf, ((xmlNsPtr) cur)->href);
	    break;
        case XML_ELEMENT_DECL:
        case XML_ATTRIBUTE_DECL:
        case XML_ENTITY_DECL:
            break;
    }
    return(0);
}