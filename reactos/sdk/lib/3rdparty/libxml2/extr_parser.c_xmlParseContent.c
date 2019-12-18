#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  char xmlChar ;
struct TYPE_13__ {scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_12__ {unsigned int consumed; char* cur; } ;

/* Variables and functions */
 scalar_t__ CMP9 (char const*,char,char,char,char,char,char,char,char,char) ; 
 char const* CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 scalar_t__ XML_PARSER_CONTENT ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlHaltParser (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParseCDSect (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParseCharData (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlParseComment (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParseElement (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParsePI (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParseReference (TYPE_2__*) ; 

void
xmlParseContent(xmlParserCtxtPtr ctxt) {
    GROW;
    while ((RAW != 0) &&
	   ((RAW != '<') || (NXT(1) != '/')) &&
	   (ctxt->instate != XML_PARSER_EOF)) {
	const xmlChar *test = CUR_PTR;
	unsigned int cons = ctxt->input->consumed;
	const xmlChar *cur = ctxt->input->cur;

	/*
	 * First case : a Processing Instruction.
	 */
	if ((*cur == '<') && (cur[1] == '?')) {
	    xmlParsePI(ctxt);
	}

	/*
	 * Second case : a CDSection
	 */
	/* 2.6.0 test was *cur not RAW */
	else if (CMP9(CUR_PTR, '<', '!', '[', 'C', 'D', 'A', 'T', 'A', '[')) {
	    xmlParseCDSect(ctxt);
	}

	/*
	 * Third case :  a comment
	 */
	else if ((*cur == '<') && (NXT(1) == '!') &&
		 (NXT(2) == '-') && (NXT(3) == '-')) {
	    xmlParseComment(ctxt);
	    ctxt->instate = XML_PARSER_CONTENT;
	}

	/*
	 * Fourth case :  a sub-element.
	 */
	else if (*cur == '<') {
	    xmlParseElement(ctxt);
	}

	/*
	 * Fifth case : a reference. If if has not been resolved,
	 *    parsing returns it's Name, create the node
	 */

	else if (*cur == '&') {
	    xmlParseReference(ctxt);
	}

	/*
	 * Last case, text. Note that References are handled directly.
	 */
	else {
	    xmlParseCharData(ctxt, 0);
	}

	GROW;
	SHRINK;

	if ((cons == ctxt->input->consumed) && (test == CUR_PTR)) {
	    xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
	                "detected an error in element content\n");
	    xmlHaltParser(ctxt);
            break;
	}
    }
}