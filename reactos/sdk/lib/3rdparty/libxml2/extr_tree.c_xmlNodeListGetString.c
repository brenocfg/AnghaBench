#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; char* content; char* name; struct TYPE_7__* next; TYPE_1__* parent; } ;
typedef  TYPE_2__ xmlNode ;
typedef  TYPE_3__* xmlEntityPtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  char xmlChar ;
struct TYPE_8__ {TYPE_2__* children; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_ENTITY_REF_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 char* xmlEncodeAttributeEntities (int /*<<< orphan*/ ,char*) ; 
 char* xmlEncodeEntitiesReentrant (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_3__* xmlGetDocEntity (int /*<<< orphan*/ ,char*) ; 
 char* xmlStrcat (char*,char*) ; 
 char* xmlStrncat (char*,char*,int) ; 

xmlChar *
xmlNodeListGetString(xmlDocPtr doc, const xmlNode *list, int inLine)
{
    const xmlNode *node = list;
    xmlChar *ret = NULL;
    xmlEntityPtr ent;
    int attr;

    if (list == NULL)
        return (NULL);
    if ((list->parent != NULL) && (list->parent->type == XML_ATTRIBUTE_NODE))
        attr = 1;
    else
        attr = 0;

    while (node != NULL) {
        if ((node->type == XML_TEXT_NODE) ||
            (node->type == XML_CDATA_SECTION_NODE)) {
            if (inLine) {
                ret = xmlStrcat(ret, node->content);
            } else {
                xmlChar *buffer;

		if (attr)
		    buffer = xmlEncodeAttributeEntities(doc, node->content);
		else
		    buffer = xmlEncodeEntitiesReentrant(doc, node->content);
                if (buffer != NULL) {
                    ret = xmlStrcat(ret, buffer);
                    xmlFree(buffer);
                }
            }
        } else if (node->type == XML_ENTITY_REF_NODE) {
            if (inLine) {
                ent = xmlGetDocEntity(doc, node->name);
                if (ent != NULL) {
                    xmlChar *buffer;

                    /* an entity content can be any "well balanced chunk",
                     * i.e. the result of the content [43] production:
                     * http://www.w3.org/TR/REC-xml#NT-content.
                     * So it can contain text, CDATA section or nested
                     * entity reference nodes (among others).
                     * -> we recursive  call xmlNodeListGetString()
                     * which handles these types */
                    buffer = xmlNodeListGetString(doc, ent->children, 1);
                    if (buffer != NULL) {
                        ret = xmlStrcat(ret, buffer);
                        xmlFree(buffer);
                    }
                } else {
                    ret = xmlStrcat(ret, node->content);
                }
            } else {
                xmlChar buf[2];

                buf[0] = '&';
                buf[1] = 0;
                ret = xmlStrncat(ret, buf, 1);
                ret = xmlStrcat(ret, node->name);
                buf[0] = ';';
                buf[1] = 0;
                ret = xmlStrncat(ret, buf, 1);
            }
        }
#if 0
        else {
            xmlGenericError(xmlGenericErrorContext,
                            "xmlGetNodeListString : invalid node type %d\n",
                            node->type);
        }
#endif
        node = node->next;
    }
    return (ret);
}