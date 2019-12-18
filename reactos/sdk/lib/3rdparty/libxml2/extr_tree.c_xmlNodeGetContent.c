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
typedef  TYPE_2__ const* xmlNodePtr ;
struct TYPE_7__ {int type; int /*<<< orphan*/ * content; int /*<<< orphan*/  name; int /*<<< orphan*/  doc; } ;
typedef  TYPE_2__ xmlNode ;
typedef  int /*<<< orphan*/ * xmlEntityPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/ * xmlBufPtr ;
typedef  int /*<<< orphan*/  xmlAttrPtr ;
struct TYPE_6__ {int /*<<< orphan*/ * href; } ;

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
 int /*<<< orphan*/ * xmlBufCreate () ; 
 int /*<<< orphan*/ * xmlBufCreateSize (int) ; 
 int /*<<< orphan*/ * xmlBufDetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlBufFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlBufGetNodeContent (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/ * xmlGetDocEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlGetPropNodeValueInternal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/ *) ; 

xmlChar *
xmlNodeGetContent(const xmlNode *cur)
{
    if (cur == NULL)
        return (NULL);
    switch (cur->type) {
        case XML_DOCUMENT_FRAG_NODE:
        case XML_ELEMENT_NODE:{
                xmlBufPtr buf;
                xmlChar *ret;

                buf = xmlBufCreateSize(64);
                if (buf == NULL)
                    return (NULL);
		xmlBufGetNodeContent(buf, cur);
                ret = xmlBufDetach(buf);
                xmlBufFree(buf);
                return (ret);
            }
        case XML_ATTRIBUTE_NODE:
	    return(xmlGetPropNodeValueInternal((xmlAttrPtr) cur));
        case XML_COMMENT_NODE:
        case XML_PI_NODE:
            if (cur->content != NULL)
                return (xmlStrdup(cur->content));
            return (NULL);
        case XML_ENTITY_REF_NODE:{
                xmlEntityPtr ent;
                xmlBufPtr buf;
                xmlChar *ret;

                /* lookup entity declaration */
                ent = xmlGetDocEntity(cur->doc, cur->name);
                if (ent == NULL)
                    return (NULL);

                buf = xmlBufCreate();
                if (buf == NULL)
                    return (NULL);

                xmlBufGetNodeContent(buf, cur);

                ret = xmlBufDetach(buf);
                xmlBufFree(buf);
                return (ret);
            }
        case XML_ENTITY_NODE:
        case XML_DOCUMENT_TYPE_NODE:
        case XML_NOTATION_NODE:
        case XML_DTD_NODE:
        case XML_XINCLUDE_START:
        case XML_XINCLUDE_END:
            return (NULL);
        case XML_DOCUMENT_NODE:
#ifdef LIBXML_DOCB_ENABLED
        case XML_DOCB_DOCUMENT_NODE:
#endif
        case XML_HTML_DOCUMENT_NODE: {
	    xmlBufPtr buf;
	    xmlChar *ret;

	    buf = xmlBufCreate();
	    if (buf == NULL)
		return (NULL);

	    xmlBufGetNodeContent(buf, (xmlNodePtr) cur);

	    ret = xmlBufDetach(buf);
	    xmlBufFree(buf);
	    return (ret);
	}
        case XML_NAMESPACE_DECL: {
	    xmlChar *tmp;

	    tmp = xmlStrdup(((xmlNsPtr) cur)->href);
            return (tmp);
	}
        case XML_ELEMENT_DECL:
            /* TODO !!! */
            return (NULL);
        case XML_ATTRIBUTE_DECL:
            /* TODO !!! */
            return (NULL);
        case XML_ENTITY_DECL:
            /* TODO !!! */
            return (NULL);
        case XML_CDATA_SECTION_NODE:
        case XML_TEXT_NODE:
            if (cur->content != NULL)
                return (xmlStrdup(cur->content));
            return (NULL);
    }
    return (NULL);
}