#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/ * children; int /*<<< orphan*/ * content; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int* space; TYPE_3__* node; int /*<<< orphan*/ * myDoc; TYPE_1__* sax; } ;
struct TYPE_5__ {scalar_t__ ignorableWhitespace; scalar_t__ characters; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_BLANK_CH (int /*<<< orphan*/  const) ; 
 char NXT (int) ; 
 char RAW ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/ * xmlGetLastChild (TYPE_3__*) ; 
 int xmlIsMixedElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlNodeIsText (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int areBlanks(xmlParserCtxtPtr ctxt, const xmlChar *str, int len,
                     int blank_chars) {
    int i, ret;
    xmlNodePtr lastChild;

    /*
     * Don't spend time trying to differentiate them, the same callback is
     * used !
     */
    if (ctxt->sax->ignorableWhitespace == ctxt->sax->characters)
	return(0);

    /*
     * Check for xml:space value.
     */
    if ((ctxt->space == NULL) || (*(ctxt->space) == 1) ||
        (*(ctxt->space) == -2))
	return(0);

    /*
     * Check that the string is made of blanks
     */
    if (blank_chars == 0) {
	for (i = 0;i < len;i++)
	    if (!(IS_BLANK_CH(str[i]))) return(0);
    }

    /*
     * Look if the element is mixed content in the DTD if available
     */
    if (ctxt->node == NULL) return(0);
    if (ctxt->myDoc != NULL) {
	ret = xmlIsMixedElement(ctxt->myDoc, ctxt->node->name);
        if (ret == 0) return(1);
        if (ret == 1) return(0);
    }

    /*
     * Otherwise, heuristic :-\
     */
    if ((RAW != '<') && (RAW != 0xD)) return(0);
    if ((ctxt->node->children == NULL) &&
	(RAW == '<') && (NXT(1) == '/')) return(0);

    lastChild = xmlGetLastChild(ctxt->node);
    if (lastChild == NULL) {
        if ((ctxt->node->type != XML_ELEMENT_NODE) &&
            (ctxt->node->content != NULL)) return(0);
    } else if (xmlNodeIsText(lastChild))
        return(0);
    else if ((ctxt->node->children != NULL) &&
             (xmlNodeIsText(ctxt->node->children)))
        return(0);
    return(1);
}