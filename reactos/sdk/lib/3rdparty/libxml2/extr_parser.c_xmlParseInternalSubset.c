#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {int inputNr; scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_8__ {unsigned int consumed; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* CUR_PTR ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_ERR_DOCTYPE_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 scalar_t__ XML_PARSER_DTD ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlParseMarkupDecl (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParsePEReference (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlPopInput (TYPE_2__*) ; 

__attribute__((used)) static void
xmlParseInternalSubset(xmlParserCtxtPtr ctxt) {
    /*
     * Is there any DTD definition ?
     */
    if (RAW == '[') {
        int baseInputNr = ctxt->inputNr;
        ctxt->instate = XML_PARSER_DTD;
        NEXT;
	/*
	 * Parse the succession of Markup declarations and
	 * PEReferences.
	 * Subsequence (markupdecl | PEReference | S)*
	 */
	while (((RAW != ']') || (ctxt->inputNr > baseInputNr)) &&
               (ctxt->instate != XML_PARSER_EOF)) {
	    const xmlChar *check = CUR_PTR;
	    unsigned int cons = ctxt->input->consumed;

	    SKIP_BLANKS;
	    xmlParseMarkupDecl(ctxt);
	    xmlParsePEReference(ctxt);

	    if ((CUR_PTR == check) && (cons == ctxt->input->consumed)) {
		xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
	     "xmlParseInternalSubset: error detected in Markup declaration\n");
                if (ctxt->inputNr > baseInputNr)
                    xmlPopInput(ctxt);
                else
		    break;
	    }
	}
	if (RAW == ']') {
	    NEXT;
	    SKIP_BLANKS;
	}
    }

    /*
     * We should be at the end of the DOCTYPE declaration.
     */
    if (RAW != '>') {
	xmlFatalErr(ctxt, XML_ERR_DOCTYPE_NOT_FINISHED, NULL);
	return;
    }
    NEXT;
}