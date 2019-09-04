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
typedef  TYPE_2__* xmlParserInputPtr ;
typedef  TYPE_3__* xmlParserCtxtPtr ;
struct TYPE_12__ {int inputNr; int options; scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_11__ {int /*<<< orphan*/  cur; } ;
struct TYPE_10__ {int filename; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_LOOP ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  inputPop (TYPE_3__*) ; 
 int inputPush (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeInputStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlParserDebugEntities ; 

int
xmlPushInput(xmlParserCtxtPtr ctxt, xmlParserInputPtr input) {
    int ret;
    if (input == NULL) return(-1);

    if (xmlParserDebugEntities) {
	if ((ctxt->input != NULL) && (ctxt->input->filename))
	    xmlGenericError(xmlGenericErrorContext,
		    "%s(%d): ", ctxt->input->filename,
		    ctxt->input->line);
	xmlGenericError(xmlGenericErrorContext,
		"Pushing input %d : %.30s\n", ctxt->inputNr+1, input->cur);
    }
    if (((ctxt->inputNr > 40) && ((ctxt->options & XML_PARSE_HUGE) == 0)) ||
        (ctxt->inputNr > 1024)) {
        xmlFatalErr(ctxt, XML_ERR_ENTITY_LOOP, NULL);
        while (ctxt->inputNr > 1)
            xmlFreeInputStream(inputPop(ctxt));
	return(-1);
    }
    ret = inputPush(ctxt, input);
    if (ctxt->instate == XML_PARSER_EOF)
        return(-1);
    GROW;
    return(ret);
}