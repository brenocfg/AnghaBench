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
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  scalar_t__ xmlCharEncoding ;
typedef  char xmlChar ;
struct TYPE_12__ {scalar_t__ errNo; scalar_t__ instate; int /*<<< orphan*/  wellFormed; int /*<<< orphan*/  userData; TYPE_2__* sax; scalar_t__ depth; scalar_t__ loadsubset; scalar_t__ validate; int /*<<< orphan*/  disableSAX; int /*<<< orphan*/  version; TYPE_1__* input; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* endDocument ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* startDocument ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setDocumentLocator ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int end; int cur; } ;

/* Variables and functions */
 scalar_t__ CMP5 (int /*<<< orphan*/ ,char,char,char,char,char) ; 
 scalar_t__ CUR ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_BLANK_CH (char) ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 scalar_t__ XML_CHAR_ENCODING_NONE ; 
 int /*<<< orphan*/  XML_DEFAULT_VERSION ; 
 int /*<<< orphan*/  XML_ERR_DOCUMENT_EMPTY ; 
 int /*<<< orphan*/  XML_ERR_EXTRA_CONTENT ; 
 int /*<<< orphan*/  XML_ERR_NOT_WELL_BALANCED ; 
 scalar_t__ XML_ERR_UNSUPPORTED_ENCODING ; 
 scalar_t__ XML_PARSER_CONTENT ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlCharStrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlDefaultSAXHandlerInit () ; 
 int /*<<< orphan*/  xmlDefaultSAXLocator ; 
 scalar_t__ xmlDetectCharEncoding (char*,int) ; 
 int /*<<< orphan*/  xmlDetectSAX2 (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlParseContent (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlParseXMLDecl (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlSwitchEncoding (TYPE_3__*,scalar_t__) ; 

int
xmlParseExtParsedEnt(xmlParserCtxtPtr ctxt) {
    xmlChar start[4];
    xmlCharEncoding enc;

    if ((ctxt == NULL) || (ctxt->input == NULL))
        return(-1);

    xmlDefaultSAXHandlerInit();

    xmlDetectSAX2(ctxt);

    GROW;

    /*
     * SAX: beginning of the document processing.
     */
    if ((ctxt->sax) && (ctxt->sax->setDocumentLocator))
        ctxt->sax->setDocumentLocator(ctxt->userData, &xmlDefaultSAXLocator);

    /*
     * Get the 4 first bytes and decode the charset
     * if enc != XML_CHAR_ENCODING_NONE
     * plug some encoding conversion routines.
     */
    if ((ctxt->input->end - ctxt->input->cur) >= 4) {
	start[0] = RAW;
	start[1] = NXT(1);
	start[2] = NXT(2);
	start[3] = NXT(3);
	enc = xmlDetectCharEncoding(start, 4);
	if (enc != XML_CHAR_ENCODING_NONE) {
	    xmlSwitchEncoding(ctxt, enc);
	}
    }


    if (CUR == 0) {
	xmlFatalErr(ctxt, XML_ERR_DOCUMENT_EMPTY, NULL);
    }

    /*
     * Check for the XMLDecl in the Prolog.
     */
    GROW;
    if ((CMP5(CUR_PTR, '<', '?', 'x', 'm', 'l')) && (IS_BLANK_CH(NXT(5)))) {

	/*
	 * Note that we will switch encoding on the fly.
	 */
	xmlParseXMLDecl(ctxt);
	if (ctxt->errNo == XML_ERR_UNSUPPORTED_ENCODING) {
	    /*
	     * The XML REC instructs us to stop parsing right here
	     */
	    return(-1);
	}
	SKIP_BLANKS;
    } else {
	ctxt->version = xmlCharStrdup(XML_DEFAULT_VERSION);
    }
    if ((ctxt->sax) && (ctxt->sax->startDocument) && (!ctxt->disableSAX))
        ctxt->sax->startDocument(ctxt->userData);
    if (ctxt->instate == XML_PARSER_EOF)
	return(-1);

    /*
     * Doing validity checking on chunk doesn't make sense
     */
    ctxt->instate = XML_PARSER_CONTENT;
    ctxt->validate = 0;
    ctxt->loadsubset = 0;
    ctxt->depth = 0;

    xmlParseContent(ctxt);
    if (ctxt->instate == XML_PARSER_EOF)
	return(-1);

    if ((RAW == '<') && (NXT(1) == '/')) {
	xmlFatalErr(ctxt, XML_ERR_NOT_WELL_BALANCED, NULL);
    } else if (RAW != 0) {
	xmlFatalErr(ctxt, XML_ERR_EXTRA_CONTENT, NULL);
    }

    /*
     * SAX: end of the document processing.
     */
    if ((ctxt->sax) && (ctxt->sax->endDocument != NULL))
        ctxt->sax->endDocument(ctxt->userData);

    if (! ctxt->wellFormed) return(-1);
    return(0);
}