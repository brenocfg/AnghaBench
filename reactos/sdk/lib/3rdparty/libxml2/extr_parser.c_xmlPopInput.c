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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_7__ {scalar_t__* cur; } ;
struct TYPE_6__ {int inputNr; scalar_t__ inSubset; scalar_t__ instate; TYPE_3__* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUR ; 
 int /*<<< orphan*/  INPUT_CHUNK ; 
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  inputPop (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFreeInputStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlParserDebugEntities ; 
 int /*<<< orphan*/  xmlParserInputGrow (TYPE_3__*,int /*<<< orphan*/ ) ; 

xmlChar
xmlPopInput(xmlParserCtxtPtr ctxt) {
    if ((ctxt == NULL) || (ctxt->inputNr <= 1)) return(0);
    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"Popping input %d\n", ctxt->inputNr);
    if ((ctxt->inputNr > 1) && (ctxt->inSubset == 0) &&
        (ctxt->instate != XML_PARSER_EOF))
        xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
                    "Unfinished entity outside the DTD");
    xmlFreeInputStream(inputPop(ctxt));
    if (*ctxt->input->cur == 0)
        xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
    return(CUR);
}