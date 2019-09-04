#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ignorableWhitespace; } ;
typedef  TYPE_2__ xmlSAXHandler ;
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_7__ {scalar_t__ nodeMax; int /*<<< orphan*/ * warning; int /*<<< orphan*/  error; TYPE_3__* userData; int /*<<< orphan*/  finishDtd; } ;
struct TYPE_9__ {int inputMax; int standalone; int nodeMax; int nameMax; int* spaceTab; int spaceMax; int spaceNr; int* space; int wellFormed; int nsWellFormed; int valid; scalar_t__ keepBlanks; int input_id; int /*<<< orphan*/  node_seq; scalar_t__ sizeentcopy; scalar_t__ sizeentities; scalar_t__ nbentities; int /*<<< orphan*/ * catalogs; int /*<<< orphan*/  charset; scalar_t__ depth; int /*<<< orphan*/  errNo; scalar_t__ inSubset; scalar_t__ checkIndex; scalar_t__ nbChars; scalar_t__ record_info; int /*<<< orphan*/  options; scalar_t__ replaceEntities; TYPE_1__ vctxt; scalar_t__ validate; TYPE_2__* sax; int /*<<< orphan*/  linenumbers; scalar_t__ pedantic; scalar_t__ loadsubset; int /*<<< orphan*/ * myDoc; struct TYPE_9__* userData; int /*<<< orphan*/ * name; scalar_t__ nameNr; int /*<<< orphan*/ * input; scalar_t__ inputNr; int /*<<< orphan*/ * node; scalar_t__ nodeNr; int /*<<< orphan*/  const** nameTab; int /*<<< orphan*/ * nodeTab; int /*<<< orphan*/ * directory; scalar_t__ token; int /*<<< orphan*/  instate; scalar_t__ external; scalar_t__ html; scalar_t__ hasPErefs; scalar_t__ hasExternalSubset; int /*<<< orphan*/ * encoding; int /*<<< orphan*/ * version; int /*<<< orphan*/ ** inputTab; int /*<<< orphan*/ * atts; scalar_t__ maxatts; int /*<<< orphan*/ * dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CHAR_ENCODING_UTF8 ; 
 int /*<<< orphan*/  XML_CTXT_FINISH_DTD_0 ; 
 int /*<<< orphan*/  XML_ERR_OK ; 
 int /*<<< orphan*/  XML_MAX_DICTIONARY_LIMIT ; 
 int /*<<< orphan*/  XML_PARSER_START ; 
 int /*<<< orphan*/  XML_PARSE_DTDLOAD ; 
 int /*<<< orphan*/  XML_PARSE_DTDVALID ; 
 int /*<<< orphan*/  XML_PARSE_NOBLANKS ; 
 int /*<<< orphan*/  XML_PARSE_NOENT ; 
 int /*<<< orphan*/  XML_PARSE_PEDANTIC ; 
 int /*<<< orphan*/ * inputPop (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlDefaultSAXHandlerInit () ; 
 int /*<<< orphan*/ * xmlDictCreate () ; 
 int /*<<< orphan*/  xmlDictSetLimit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlDoValidityCheckingDefaultValue ; 
 int /*<<< orphan*/  xmlErrInternal (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlErrMemory (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xmlFreeInputStream (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlGetWarningsDefaultValue ; 
 int /*<<< orphan*/  xmlInitNodeInfoSeq (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlKeepBlanksDefaultValue ; 
 int /*<<< orphan*/  xmlLineNumbersDefaultValue ; 
 scalar_t__ xmlLoadExtDtdDefaultValue ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlParserValidityError ; 
 void* xmlParserValidityWarning ; 
 scalar_t__ xmlPedanticParserDefaultValue ; 
 int /*<<< orphan*/  xmlSAX2IgnorableWhitespace ; 
 int /*<<< orphan*/  xmlSAXVersion (TYPE_2__*,int) ; 
 scalar_t__ xmlSubstituteEntitiesDefaultValue ; 

int
xmlInitParserCtxt(xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr input;

    if(ctxt==NULL) {
        xmlErrInternal(NULL, "Got NULL parser context\n", NULL);
        return(-1);
    }

    xmlDefaultSAXHandlerInit();

    if (ctxt->dict == NULL)
	ctxt->dict = xmlDictCreate();
    if (ctxt->dict == NULL) {
        xmlErrMemory(NULL, "cannot initialize parser context\n");
	return(-1);
    }
    xmlDictSetLimit(ctxt->dict, XML_MAX_DICTIONARY_LIMIT);

    if (ctxt->sax == NULL)
	ctxt->sax = (xmlSAXHandler *) xmlMalloc(sizeof(xmlSAXHandler));
    if (ctxt->sax == NULL) {
        xmlErrMemory(NULL, "cannot initialize parser context\n");
	return(-1);
    }
    else
        xmlSAXVersion(ctxt->sax, 2);

    ctxt->maxatts = 0;
    ctxt->atts = NULL;
    /* Allocate the Input stack */
    if (ctxt->inputTab == NULL) {
	ctxt->inputTab = (xmlParserInputPtr *)
		    xmlMalloc(5 * sizeof(xmlParserInputPtr));
	ctxt->inputMax = 5;
    }
    if (ctxt->inputTab == NULL) {
        xmlErrMemory(NULL, "cannot initialize parser context\n");
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = NULL;
	return(-1);
    }
    while ((input = inputPop(ctxt)) != NULL) { /* Non consuming */
        xmlFreeInputStream(input);
    }
    ctxt->inputNr = 0;
    ctxt->input = NULL;

    ctxt->version = NULL;
    ctxt->encoding = NULL;
    ctxt->standalone = -1;
    ctxt->hasExternalSubset = 0;
    ctxt->hasPErefs = 0;
    ctxt->html = 0;
    ctxt->external = 0;
    ctxt->instate = XML_PARSER_START;
    ctxt->token = 0;
    ctxt->directory = NULL;

    /* Allocate the Node stack */
    if (ctxt->nodeTab == NULL) {
	ctxt->nodeTab = (xmlNodePtr *) xmlMalloc(10 * sizeof(xmlNodePtr));
	ctxt->nodeMax = 10;
    }
    if (ctxt->nodeTab == NULL) {
        xmlErrMemory(NULL, "cannot initialize parser context\n");
	ctxt->nodeNr = 0;
	ctxt->nodeMax = 0;
	ctxt->node = NULL;
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = NULL;
	return(-1);
    }
    ctxt->nodeNr = 0;
    ctxt->node = NULL;

    /* Allocate the Name stack */
    if (ctxt->nameTab == NULL) {
	ctxt->nameTab = (const xmlChar **) xmlMalloc(10 * sizeof(xmlChar *));
	ctxt->nameMax = 10;
    }
    if (ctxt->nameTab == NULL) {
        xmlErrMemory(NULL, "cannot initialize parser context\n");
	ctxt->nodeNr = 0;
	ctxt->nodeMax = 0;
	ctxt->node = NULL;
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = NULL;
	ctxt->nameNr = 0;
	ctxt->nameMax = 0;
	ctxt->name = NULL;
	return(-1);
    }
    ctxt->nameNr = 0;
    ctxt->name = NULL;

    /* Allocate the space stack */
    if (ctxt->spaceTab == NULL) {
	ctxt->spaceTab = (int *) xmlMalloc(10 * sizeof(int));
	ctxt->spaceMax = 10;
    }
    if (ctxt->spaceTab == NULL) {
        xmlErrMemory(NULL, "cannot initialize parser context\n");
	ctxt->nodeNr = 0;
	ctxt->nodeMax = 0;
	ctxt->node = NULL;
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = NULL;
	ctxt->nameNr = 0;
	ctxt->nameMax = 0;
	ctxt->name = NULL;
	ctxt->spaceNr = 0;
	ctxt->spaceMax = 0;
	ctxt->space = NULL;
	return(-1);
    }
    ctxt->spaceNr = 1;
    ctxt->spaceMax = 10;
    ctxt->spaceTab[0] = -1;
    ctxt->space = &ctxt->spaceTab[0];
    ctxt->userData = ctxt;
    ctxt->myDoc = NULL;
    ctxt->wellFormed = 1;
    ctxt->nsWellFormed = 1;
    ctxt->valid = 1;
    ctxt->loadsubset = xmlLoadExtDtdDefaultValue;
    if (ctxt->loadsubset) {
        ctxt->options |= XML_PARSE_DTDLOAD;
    }
    ctxt->validate = xmlDoValidityCheckingDefaultValue;
    ctxt->pedantic = xmlPedanticParserDefaultValue;
    if (ctxt->pedantic) {
        ctxt->options |= XML_PARSE_PEDANTIC;
    }
    ctxt->linenumbers = xmlLineNumbersDefaultValue;
    ctxt->keepBlanks = xmlKeepBlanksDefaultValue;
    if (ctxt->keepBlanks == 0) {
	ctxt->sax->ignorableWhitespace = xmlSAX2IgnorableWhitespace;
	ctxt->options |= XML_PARSE_NOBLANKS;
    }

    ctxt->vctxt.finishDtd = XML_CTXT_FINISH_DTD_0;
    ctxt->vctxt.userData = ctxt;
    ctxt->vctxt.error = xmlParserValidityError;
    ctxt->vctxt.warning = xmlParserValidityWarning;
    if (ctxt->validate) {
	if (xmlGetWarningsDefaultValue == 0)
	    ctxt->vctxt.warning = NULL;
	else
	    ctxt->vctxt.warning = xmlParserValidityWarning;
	ctxt->vctxt.nodeMax = 0;
        ctxt->options |= XML_PARSE_DTDVALID;
    }
    ctxt->replaceEntities = xmlSubstituteEntitiesDefaultValue;
    if (ctxt->replaceEntities) {
        ctxt->options |= XML_PARSE_NOENT;
    }
    ctxt->record_info = 0;
    ctxt->nbChars = 0;
    ctxt->checkIndex = 0;
    ctxt->inSubset = 0;
    ctxt->errNo = XML_ERR_OK;
    ctxt->depth = 0;
    ctxt->charset = XML_CHAR_ENCODING_UTF8;
    ctxt->catalogs = NULL;
    ctxt->nbentities = 0;
    ctxt->sizeentities = 0;
    ctxt->sizeentcopy = 0;
    ctxt->input_id = 1;
    xmlInitNodeInfoSeq(&ctxt->node_seq);
    return(0);
}