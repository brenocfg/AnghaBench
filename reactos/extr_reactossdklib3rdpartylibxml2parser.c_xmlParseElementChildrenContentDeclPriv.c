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
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  TYPE_3__* xmlElementContentPtr ;
typedef  int xmlChar ;
struct TYPE_15__ {scalar_t__ ocur; scalar_t__ type; struct TYPE_15__* c2; struct TYPE_15__* c1; struct TYPE_15__* parent; } ;
struct TYPE_14__ {int options; scalar_t__ instate; TYPE_1__* input; int /*<<< orphan*/  myDoc; } ;
struct TYPE_13__ {int id; } ;

/* Variables and functions */
 int CUR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 scalar_t__ XML_ELEMENT_CONTENT_ELEMENT ; 
 scalar_t__ XML_ELEMENT_CONTENT_MULT ; 
 void* XML_ELEMENT_CONTENT_ONCE ; 
 scalar_t__ XML_ELEMENT_CONTENT_OPT ; 
 scalar_t__ XML_ELEMENT_CONTENT_OR ; 
 scalar_t__ XML_ELEMENT_CONTENT_PLUS ; 
 scalar_t__ XML_ELEMENT_CONTENT_SEQ ; 
 int /*<<< orphan*/  XML_ERR_ELEMCONTENT_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_ELEMCONTENT_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_BOUNDARY ; 
 int /*<<< orphan*/  XML_ERR_SEPARATOR_REQUIRED ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlFreeDocElementContent (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* xmlNewDocElementContent (int /*<<< orphan*/ ,int const*,scalar_t__) ; 
 int* xmlParseName (TYPE_2__*) ; 

__attribute__((used)) static xmlElementContentPtr
xmlParseElementChildrenContentDeclPriv(xmlParserCtxtPtr ctxt, int inputchk,
                                       int depth) {
    xmlElementContentPtr ret = NULL, cur = NULL, last = NULL, op = NULL;
    const xmlChar *elem;
    xmlChar type = 0;

    if (((depth > 128) && ((ctxt->options & XML_PARSE_HUGE) == 0)) ||
        (depth >  2048)) {
        xmlFatalErrMsgInt(ctxt, XML_ERR_ELEMCONTENT_NOT_FINISHED,
"xmlParseElementChildrenContentDecl : depth %d too deep, use XML_PARSE_HUGE\n",
                          depth);
	return(NULL);
    }
    SKIP_BLANKS;
    GROW;
    if (RAW == '(') {
	int inputid = ctxt->input->id;

        /* Recurse on first child */
	NEXT;
	SKIP_BLANKS;
        cur = ret = xmlParseElementChildrenContentDeclPriv(ctxt, inputid,
                                                           depth + 1);
	SKIP_BLANKS;
	GROW;
    } else {
	elem = xmlParseName(ctxt);
	if (elem == NULL) {
	    xmlFatalErr(ctxt, XML_ERR_ELEMCONTENT_NOT_STARTED, NULL);
	    return(NULL);
	}
        cur = ret = xmlNewDocElementContent(ctxt->myDoc, elem, XML_ELEMENT_CONTENT_ELEMENT);
	if (cur == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    return(NULL);
	}
	GROW;
	if (RAW == '?') {
	    cur->ocur = XML_ELEMENT_CONTENT_OPT;
	    NEXT;
	} else if (RAW == '*') {
	    cur->ocur = XML_ELEMENT_CONTENT_MULT;
	    NEXT;
	} else if (RAW == '+') {
	    cur->ocur = XML_ELEMENT_CONTENT_PLUS;
	    NEXT;
	} else {
	    cur->ocur = XML_ELEMENT_CONTENT_ONCE;
	}
	GROW;
    }
    SKIP_BLANKS;
    SHRINK;
    while ((RAW != ')') && (ctxt->instate != XML_PARSER_EOF)) {
        /*
	 * Each loop we parse one separator and one element.
	 */
        if (RAW == ',') {
	    if (type == 0) type = CUR;

	    /*
	     * Detect "Name | Name , Name" error
	     */
	    else if (type != CUR) {
		xmlFatalErrMsgInt(ctxt, XML_ERR_SEPARATOR_REQUIRED,
		    "xmlParseElementChildrenContentDecl : '%c' expected\n",
		                  type);
		if ((last != NULL) && (last != ret))
		    xmlFreeDocElementContent(ctxt->myDoc, last);
		if (ret != NULL)
		    xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    NEXT;

	    op = xmlNewDocElementContent(ctxt->myDoc, NULL, XML_ELEMENT_CONTENT_SEQ);
	    if (op == NULL) {
		if ((last != NULL) && (last != ret))
		    xmlFreeDocElementContent(ctxt->myDoc, last);
	        xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    if (last == NULL) {
		op->c1 = ret;
		if (ret != NULL)
		    ret->parent = op;
		ret = cur = op;
	    } else {
	        cur->c2 = op;
		if (op != NULL)
		    op->parent = cur;
		op->c1 = last;
		if (last != NULL)
		    last->parent = op;
		cur =op;
		last = NULL;
	    }
	} else if (RAW == '|') {
	    if (type == 0) type = CUR;

	    /*
	     * Detect "Name , Name | Name" error
	     */
	    else if (type != CUR) {
		xmlFatalErrMsgInt(ctxt, XML_ERR_SEPARATOR_REQUIRED,
		    "xmlParseElementChildrenContentDecl : '%c' expected\n",
				  type);
		if ((last != NULL) && (last != ret))
		    xmlFreeDocElementContent(ctxt->myDoc, last);
		if (ret != NULL)
		    xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    NEXT;

	    op = xmlNewDocElementContent(ctxt->myDoc, NULL, XML_ELEMENT_CONTENT_OR);
	    if (op == NULL) {
		if ((last != NULL) && (last != ret))
		    xmlFreeDocElementContent(ctxt->myDoc, last);
		if (ret != NULL)
		    xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    if (last == NULL) {
		op->c1 = ret;
		if (ret != NULL)
		    ret->parent = op;
		ret = cur = op;
	    } else {
	        cur->c2 = op;
		if (op != NULL)
		    op->parent = cur;
		op->c1 = last;
		if (last != NULL)
		    last->parent = op;
		cur =op;
		last = NULL;
	    }
	} else {
	    xmlFatalErr(ctxt, XML_ERR_ELEMCONTENT_NOT_FINISHED, NULL);
	    if ((last != NULL) && (last != ret))
	        xmlFreeDocElementContent(ctxt->myDoc, last);
	    if (ret != NULL)
		xmlFreeDocElementContent(ctxt->myDoc, ret);
	    return(NULL);
	}
	GROW;
	SKIP_BLANKS;
	GROW;
	if (RAW == '(') {
	    int inputid = ctxt->input->id;
	    /* Recurse on second child */
	    NEXT;
	    SKIP_BLANKS;
	    last = xmlParseElementChildrenContentDeclPriv(ctxt, inputid,
                                                          depth + 1);
	    SKIP_BLANKS;
	} else {
	    elem = xmlParseName(ctxt);
	    if (elem == NULL) {
		xmlFatalErr(ctxt, XML_ERR_ELEMCONTENT_NOT_STARTED, NULL);
		if (ret != NULL)
		    xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    last = xmlNewDocElementContent(ctxt->myDoc, elem, XML_ELEMENT_CONTENT_ELEMENT);
	    if (last == NULL) {
		if (ret != NULL)
		    xmlFreeDocElementContent(ctxt->myDoc, ret);
		return(NULL);
	    }
	    if (RAW == '?') {
		last->ocur = XML_ELEMENT_CONTENT_OPT;
		NEXT;
	    } else if (RAW == '*') {
		last->ocur = XML_ELEMENT_CONTENT_MULT;
		NEXT;
	    } else if (RAW == '+') {
		last->ocur = XML_ELEMENT_CONTENT_PLUS;
		NEXT;
	    } else {
		last->ocur = XML_ELEMENT_CONTENT_ONCE;
	    }
	}
	SKIP_BLANKS;
	GROW;
    }
    if ((cur != NULL) && (last != NULL)) {
        cur->c2 = last;
	if (last != NULL)
	    last->parent = cur;
    }
    if (ctxt->input->id != inputchk) {
	xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
                       "Element content declaration doesn't start and stop in"
                       " the same entity\n");
    }
    NEXT;
    if (RAW == '?') {
	if (ret != NULL) {
	    if ((ret->ocur == XML_ELEMENT_CONTENT_PLUS) ||
	        (ret->ocur == XML_ELEMENT_CONTENT_MULT))
	        ret->ocur = XML_ELEMENT_CONTENT_MULT;
	    else
	        ret->ocur = XML_ELEMENT_CONTENT_OPT;
	}
	NEXT;
    } else if (RAW == '*') {
	if (ret != NULL) {
	    ret->ocur = XML_ELEMENT_CONTENT_MULT;
	    cur = ret;
	    /*
	     * Some normalization:
	     * (a | b* | c?)* == (a | b | c)*
	     */
	    while ((cur != NULL) && (cur->type == XML_ELEMENT_CONTENT_OR)) {
		if ((cur->c1 != NULL) &&
	            ((cur->c1->ocur == XML_ELEMENT_CONTENT_OPT) ||
		     (cur->c1->ocur == XML_ELEMENT_CONTENT_MULT)))
		    cur->c1->ocur = XML_ELEMENT_CONTENT_ONCE;
		if ((cur->c2 != NULL) &&
	            ((cur->c2->ocur == XML_ELEMENT_CONTENT_OPT) ||
		     (cur->c2->ocur == XML_ELEMENT_CONTENT_MULT)))
		    cur->c2->ocur = XML_ELEMENT_CONTENT_ONCE;
		cur = cur->c2;
	    }
	}
	NEXT;
    } else if (RAW == '+') {
	if (ret != NULL) {
	    int found = 0;

	    if ((ret->ocur == XML_ELEMENT_CONTENT_OPT) ||
	        (ret->ocur == XML_ELEMENT_CONTENT_MULT))
	        ret->ocur = XML_ELEMENT_CONTENT_MULT;
	    else
	        ret->ocur = XML_ELEMENT_CONTENT_PLUS;
	    /*
	     * Some normalization:
	     * (a | b*)+ == (a | b)*
	     * (a | b?)+ == (a | b)*
	     */
	    while ((cur != NULL) && (cur->type == XML_ELEMENT_CONTENT_OR)) {
		if ((cur->c1 != NULL) &&
	            ((cur->c1->ocur == XML_ELEMENT_CONTENT_OPT) ||
		     (cur->c1->ocur == XML_ELEMENT_CONTENT_MULT))) {
		    cur->c1->ocur = XML_ELEMENT_CONTENT_ONCE;
		    found = 1;
		}
		if ((cur->c2 != NULL) &&
	            ((cur->c2->ocur == XML_ELEMENT_CONTENT_OPT) ||
		     (cur->c2->ocur == XML_ELEMENT_CONTENT_MULT))) {
		    cur->c2->ocur = XML_ELEMENT_CONTENT_ONCE;
		    found = 1;
		}
		cur = cur->c2;
	    }
	    if (found)
		ret->ocur = XML_ELEMENT_CONTENT_MULT;
	}
	NEXT;
    }
    return(ret);
}