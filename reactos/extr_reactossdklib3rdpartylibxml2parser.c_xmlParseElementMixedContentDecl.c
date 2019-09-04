#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  TYPE_3__* xmlElementContentPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_12__ {void* ocur; struct TYPE_12__* parent; struct TYPE_12__* c2; struct TYPE_12__* c1; } ;
struct TYPE_11__ {scalar_t__ instate; int /*<<< orphan*/  myDoc; TYPE_1__* input; } ;
struct TYPE_10__ {int id; } ;

/* Variables and functions */
 scalar_t__ CMP7 (int /*<<< orphan*/ ,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_ELEMENT_CONTENT_ELEMENT ; 
 void* XML_ELEMENT_CONTENT_MULT ; 
 int /*<<< orphan*/  XML_ELEMENT_CONTENT_OR ; 
 int /*<<< orphan*/  XML_ELEMENT_CONTENT_PCDATA ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_BOUNDARY ; 
 int /*<<< orphan*/  XML_ERR_MIXED_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_NAME_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_PCDATA_REQUIRED ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFreeDocElementContent (int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* xmlNewDocElementContent (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_2__*) ; 

xmlElementContentPtr
xmlParseElementMixedContentDecl(xmlParserCtxtPtr ctxt, int inputchk) {
    xmlElementContentPtr ret = NULL, cur = NULL, n;
    const xmlChar *elem = NULL;

    GROW;
    if (CMP7(CUR_PTR, '#', 'P', 'C', 'D', 'A', 'T', 'A')) {
	SKIP(7);
	SKIP_BLANKS;
	SHRINK;
	if (RAW == ')') {
	    if (ctxt->input->id != inputchk) {
		xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
                               "Element content declaration doesn't start and"
                               " stop in the same entity\n");
	    }
	    NEXT;
	    ret = xmlNewDocElementContent(ctxt->myDoc, NULL, XML_ELEMENT_CONTENT_PCDATA);
	    if (ret == NULL)
	        return(NULL);
	    if (RAW == '*') {
		ret->ocur = XML_ELEMENT_CONTENT_MULT;
		NEXT;
	    }
	    return(ret);
	}
	if ((RAW == '(') || (RAW == '|')) {
	    ret = cur = xmlNewDocElementContent(ctxt->myDoc, NULL, XML_ELEMENT_CONTENT_PCDATA);
	    if (ret == NULL) return(NULL);
	}
	while ((RAW == '|') && (ctxt->instate != XML_PARSER_EOF)) {
	    NEXT;
	    if (elem == NULL) {
	        ret = xmlNewDocElementContent(ctxt->myDoc, NULL, XML_ELEMENT_CONTENT_OR);
		if (ret == NULL) return(NULL);
		ret->c1 = cur;
		if (cur != NULL)
		    cur->parent = ret;
		cur = ret;
	    } else {
	        n = xmlNewDocElementContent(ctxt->myDoc, NULL, XML_ELEMENT_CONTENT_OR);
		if (n == NULL) return(NULL);
		n->c1 = xmlNewDocElementContent(ctxt->myDoc, elem, XML_ELEMENT_CONTENT_ELEMENT);
		if (n->c1 != NULL)
		    n->c1->parent = n;
	        cur->c2 = n;
		if (n != NULL)
		    n->parent = cur;
		cur = n;
	    }
	    SKIP_BLANKS;
	    elem = xmlParseName(ctxt);
	    if (elem == NULL) {
		xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
			"xmlParseElementMixedContentDecl : Name expected\n");
		xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    SKIP_BLANKS;
	    GROW;
	}
	if ((RAW == ')') && (NXT(1) == '*')) {
	    if (elem != NULL) {
		cur->c2 = xmlNewDocElementContent(ctxt->myDoc, elem,
		                               XML_ELEMENT_CONTENT_ELEMENT);
		if (cur->c2 != NULL)
		    cur->c2->parent = cur;
            }
            if (ret != NULL)
                ret->ocur = XML_ELEMENT_CONTENT_MULT;
	    if (ctxt->input->id != inputchk) {
		xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
                               "Element content declaration doesn't start and"
                               " stop in the same entity\n");
	    }
	    SKIP(2);
	} else {
	    xmlFreeDocElementContent(ctxt->myDoc, ret);
	    xmlFatalErr(ctxt, XML_ERR_MIXED_NOT_STARTED, NULL);
	    return(NULL);
	}

    } else {
	xmlFatalErr(ctxt, XML_ERR_PCDATA_REQUIRED, NULL);
    }
    return(ret);
}