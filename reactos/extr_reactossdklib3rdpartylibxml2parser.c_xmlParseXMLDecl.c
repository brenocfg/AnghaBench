#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  char xmlChar ;
struct TYPE_12__ {int options; char* version; scalar_t__ errNo; scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_11__ {int standalone; int /*<<< orphan*/ * encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  IS_BLANK_CH (char) ; 
 int /*<<< orphan*/  MOVETO_ENDTAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 scalar_t__ XML_DEFAULT_VERSION ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_UNKNOWN_VERSION ; 
 scalar_t__ XML_ERR_UNSUPPORTED_ENCODING ; 
 int /*<<< orphan*/  XML_ERR_VERSION_MISSING ; 
 int /*<<< orphan*/  XML_ERR_XMLDECL_NOT_FINISHED ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_OLD10 ; 
 int /*<<< orphan*/  XML_WAR_UNKNOWN_VERSION ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFatalErrMsgStr (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xmlFree (void*) ; 
 int /*<<< orphan*/  xmlParseEncodingDecl (TYPE_2__*) ; 
 int xmlParseSDDecl (TYPE_2__*) ; 
 char* xmlParseVersionInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlStrEqual (char*,char const*) ; 
 int /*<<< orphan*/  xmlWarningMsg (TYPE_2__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 

void
xmlParseXMLDecl(xmlParserCtxtPtr ctxt) {
    xmlChar *version;

    /*
     * This value for standalone indicates that the document has an
     * XML declaration but it does not have a standalone attribute.
     * It will be overwritten later if a standalone attribute is found.
     */
    ctxt->input->standalone = -2;

    /*
     * We know that '<?xml' is here.
     */
    SKIP(5);

    if (!IS_BLANK_CH(RAW)) {
	xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
	               "Blank needed after '<?xml'\n");
    }
    SKIP_BLANKS;

    /*
     * We must have the VersionInfo here.
     */
    version = xmlParseVersionInfo(ctxt);
    if (version == NULL) {
	xmlFatalErr(ctxt, XML_ERR_VERSION_MISSING, NULL);
    } else {
	if (!xmlStrEqual(version, (const xmlChar *) XML_DEFAULT_VERSION)) {
	    /*
	     * Changed here for XML-1.0 5th edition
	     */
	    if (ctxt->options & XML_PARSE_OLD10) {
		xmlFatalErrMsgStr(ctxt, XML_ERR_UNKNOWN_VERSION,
			          "Unsupported version '%s'\n",
			          version);
	    } else {
	        if ((version[0] == '1') && ((version[1] == '.'))) {
		    xmlWarningMsg(ctxt, XML_WAR_UNKNOWN_VERSION,
		                  "Unsupported version '%s'\n",
				  version, NULL);
		} else {
		    xmlFatalErrMsgStr(ctxt, XML_ERR_UNKNOWN_VERSION,
				      "Unsupported version '%s'\n",
				      version);
		}
	    }
	}
	if (ctxt->version != NULL)
	    xmlFree((void *) ctxt->version);
	ctxt->version = version;
    }

    /*
     * We may have the encoding declaration
     */
    if (!IS_BLANK_CH(RAW)) {
        if ((RAW == '?') && (NXT(1) == '>')) {
	    SKIP(2);
	    return;
	}
	xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED, "Blank needed here\n");
    }
    xmlParseEncodingDecl(ctxt);
    if ((ctxt->errNo == XML_ERR_UNSUPPORTED_ENCODING) ||
         (ctxt->instate == XML_PARSER_EOF)) {
	/*
	 * The XML REC instructs us to stop parsing right here
	 */
        return;
    }

    /*
     * We may have the standalone status.
     */
    if ((ctxt->input->encoding != NULL) && (!IS_BLANK_CH(RAW))) {
        if ((RAW == '?') && (NXT(1) == '>')) {
	    SKIP(2);
	    return;
	}
	xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED, "Blank needed here\n");
    }

    /*
     * We can grow the input buffer freely at that point
     */
    GROW;

    SKIP_BLANKS;
    ctxt->input->standalone = xmlParseSDDecl(ctxt);

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