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
struct TYPE_9__ {scalar_t__ errNo; TYPE_1__* input; } ;
struct TYPE_8__ {int /*<<< orphan*/ * version; } ;

/* Variables and functions */
 scalar_t__ CMP5 (int /*<<< orphan*/ ,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 scalar_t__ IS_BLANK_CH (char) ; 
 int /*<<< orphan*/  MOVETO_ENDTAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 scalar_t__ SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_DEFAULT_VERSION ; 
 int /*<<< orphan*/  XML_ERR_MISSING_ENCODING ; 
 scalar_t__ XML_ERR_OK ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 scalar_t__ XML_ERR_UNSUPPORTED_ENCODING ; 
 int /*<<< orphan*/  XML_ERR_XMLDECL_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_XMLDECL_NOT_STARTED ; 
 int /*<<< orphan*/ * xmlCharStrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xmlParseEncodingDecl (TYPE_2__*) ; 
 int /*<<< orphan*/ * xmlParseVersionInfo (TYPE_2__*) ; 

void
xmlParseTextDecl(xmlParserCtxtPtr ctxt) {
    xmlChar *version;
    const xmlChar *encoding;

    /*
     * We know that '<?xml' is here.
     */
    if ((CMP5(CUR_PTR, '<', '?', 'x', 'm', 'l')) && (IS_BLANK_CH(NXT(5)))) {
	SKIP(5);
    } else {
	xmlFatalErr(ctxt, XML_ERR_XMLDECL_NOT_STARTED, NULL);
	return;
    }

    if (SKIP_BLANKS == 0) {
	xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
		       "Space needed after '<?xml'\n");
    }

    /*
     * We may have the VersionInfo here.
     */
    version = xmlParseVersionInfo(ctxt);
    if (version == NULL)
	version = xmlCharStrdup(XML_DEFAULT_VERSION);
    else {
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
		           "Space needed here\n");
	}
    }
    ctxt->input->version = version;

    /*
     * We must have the encoding declaration
     */
    encoding = xmlParseEncodingDecl(ctxt);
    if (ctxt->errNo == XML_ERR_UNSUPPORTED_ENCODING) {
	/*
	 * The XML REC instructs us to stop parsing right here
	 */
        return;
    }
    if ((encoding == NULL) && (ctxt->errNo == XML_ERR_OK)) {
	xmlFatalErrMsg(ctxt, XML_ERR_MISSING_ENCODING,
		       "Missing encoding in text declaration\n");
    }

    SKIP_BLANKS;
    if ((RAW == '?') && (NXT(1) == '>')) {
        SKIP(2);
    } else if (RAW == '>') {
        /* Deprecated old WD ... */
	xmlFatalErr(ctxt, XML_ERR_XMLDECL_NOT_FINISHED, NULL);
	NEXT;
    } else {
	xmlFatalErr(ctxt, XML_ERR_XMLDECL_NOT_FINISHED, NULL);
	MOVETO_ENDTAG(CUR_PTR);
	NEXT;
    }
}