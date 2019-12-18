#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/ * content; int /*<<< orphan*/ * properties; TYPE_1__* doc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dict; } ;

/* Variables and functions */
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_COMMENT_NODE ; 
 scalar_t__ XML_PI_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 
 scalar_t__ xmlDictOwns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/ * xmlStrncat (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * xmlStrncatNew (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int
xmlTextConcat(xmlNodePtr node, const xmlChar *content, int len) {
    if (node == NULL) return(-1);

    if ((node->type != XML_TEXT_NODE) &&
        (node->type != XML_CDATA_SECTION_NODE) &&
	(node->type != XML_COMMENT_NODE) &&
	(node->type != XML_PI_NODE)) {
#ifdef DEBUG_TREE
	xmlGenericError(xmlGenericErrorContext,
		"xmlTextConcat: node is not text nor CDATA\n");
#endif
        return(-1);
    }
    /* need to check if content is currently in the dictionary */
    if ((node->content == (xmlChar *) &(node->properties)) ||
        ((node->doc != NULL) && (node->doc->dict != NULL) &&
		xmlDictOwns(node->doc->dict, node->content))) {
	node->content = xmlStrncatNew(node->content, content, len);
    } else {
        node->content = xmlStrncat(node->content, content, len);
    }
    node->properties = NULL;
    if (node->content == NULL)
        return(-1);
    return(0);
}