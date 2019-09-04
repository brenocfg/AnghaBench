#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  TYPE_4__* xmlElementContentPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_15__ {scalar_t__ external; int inputNr; int /*<<< orphan*/  myDoc; int /*<<< orphan*/  userData; TYPE_2__* sax; int /*<<< orphan*/  disableSAX; TYPE_1__* input; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* elementDecl ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,TYPE_4__*) ;} ;
struct TYPE_13__ {int id; } ;

/* Variables and functions */
 scalar_t__ CMP5 (int /*<<< orphan*/ ,char,char,char,char,char) ; 
 scalar_t__ CMP9 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 scalar_t__ SKIP_BLANKS ; 
 int XML_ELEMENT_TYPE_ANY ; 
 int XML_ELEMENT_TYPE_EMPTY ; 
 int /*<<< orphan*/  XML_ERR_ELEMCONTENT_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_BOUNDARY ; 
 int /*<<< orphan*/  XML_ERR_GT_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_NAME_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_PEREF_IN_INT_SUBSET ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFreeDocElementContent (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int xmlParseElementContentDecl (TYPE_3__*,int /*<<< orphan*/  const*,TYPE_4__**) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_3__*) ; 

int
xmlParseElementDecl(xmlParserCtxtPtr ctxt) {
    const xmlChar *name;
    int ret = -1;
    xmlElementContentPtr content  = NULL;

    /* GROW; done in the caller */
    if (CMP9(CUR_PTR, '<', '!', 'E', 'L', 'E', 'M', 'E', 'N', 'T')) {
	int inputid = ctxt->input->id;

	SKIP(9);
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
		           "Space required after 'ELEMENT'\n");
	    return(-1);
	}
        name = xmlParseName(ctxt);
	if (name == NULL) {
	    xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
			   "xmlParseElementDecl: no name for Element\n");
	    return(-1);
	}
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
			   "Space required after the element name\n");
	}
	if (CMP5(CUR_PTR, 'E', 'M', 'P', 'T', 'Y')) {
	    SKIP(5);
	    /*
	     * Element must always be empty.
	     */
	    ret = XML_ELEMENT_TYPE_EMPTY;
	} else if ((RAW == 'A') && (NXT(1) == 'N') &&
	           (NXT(2) == 'Y')) {
	    SKIP(3);
	    /*
	     * Element is a generic container.
	     */
	    ret = XML_ELEMENT_TYPE_ANY;
	} else if (RAW == '(') {
	    ret = xmlParseElementContentDecl(ctxt, name, &content);
	} else {
	    /*
	     * [ WFC: PEs in Internal Subset ] error handling.
	     */
	    if ((RAW == '%') && (ctxt->external == 0) &&
	        (ctxt->inputNr == 1)) {
		xmlFatalErrMsg(ctxt, XML_ERR_PEREF_IN_INT_SUBSET,
	  "PEReference: forbidden within markup decl in internal subset\n");
	    } else {
		xmlFatalErrMsg(ctxt, XML_ERR_ELEMCONTENT_NOT_STARTED,
		      "xmlParseElementDecl: 'EMPTY', 'ANY' or '(' expected\n");
            }
	    return(-1);
	}

	SKIP_BLANKS;

	if (RAW != '>') {
	    xmlFatalErr(ctxt, XML_ERR_GT_REQUIRED, NULL);
	    if (content != NULL) {
		xmlFreeDocElementContent(ctxt->myDoc, content);
	    }
	} else {
	    if (inputid != ctxt->input->id) {
		xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
                               "Element declaration doesn't start and stop in"
                               " the same entity\n");
	    }

	    NEXT;
	    if ((ctxt->sax != NULL) && (!ctxt->disableSAX) &&
		(ctxt->sax->elementDecl != NULL)) {
		if (content != NULL)
		    content->parent = NULL;
	        ctxt->sax->elementDecl(ctxt->userData, name, ret,
		                       content);
		if ((content != NULL) && (content->parent == NULL)) {
		    /*
		     * this is a trick: if xmlAddElementDecl is called,
		     * instead of copying the full tree it is plugged directly
		     * if called from the parser. Avoid duplicating the
		     * interfaces or change the API/ABI
		     */
		    xmlFreeDocElementContent(ctxt->myDoc, content);
		}
	    } else if (content != NULL) {
		xmlFreeDocElementContent(ctxt->myDoc, content);
	    }
	}
    }
    return(ret);
}