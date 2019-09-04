#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_8__ {int* space; scalar_t__ instate; TYPE_1__* sax; int /*<<< orphan*/  userData; int /*<<< orphan*/  disableSAX; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* ignorableWhitespace ) (int /*<<< orphan*/ ,scalar_t__*,int) ;int /*<<< orphan*/  (* characters ) (int /*<<< orphan*/ ,scalar_t__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,scalar_t__*,int,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 char NXT (int) ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHAR ; 
 int /*<<< orphan*/  XML_ERR_MISPLACED_CDATA_END ; 
 int XML_PARSER_BIG_BUFFER_SIZE ; 
 scalar_t__ XML_PARSER_CONTENT ; 
 scalar_t__ XML_PARSER_EOF ; 
 scalar_t__ areBlanks (TYPE_2__*,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
xmlParseCharDataComplex(xmlParserCtxtPtr ctxt, int cdata) {
    xmlChar buf[XML_PARSER_BIG_BUFFER_SIZE + 5];
    int nbchar = 0;
    int cur, l;
    int count = 0;

    SHRINK;
    GROW;
    cur = CUR_CHAR(l);
    while ((cur != '<') && /* checked */
           (cur != '&') &&
	   (IS_CHAR(cur))) /* test also done in xmlCurrentChar() */ {
	if ((cur == ']') && (NXT(1) == ']') &&
	    (NXT(2) == '>')) {
	    if (cdata) break;
	    else {
		xmlFatalErr(ctxt, XML_ERR_MISPLACED_CDATA_END, NULL);
	    }
	}
	COPY_BUF(l,buf,nbchar,cur);
	if (nbchar >= XML_PARSER_BIG_BUFFER_SIZE) {
	    buf[nbchar] = 0;

	    /*
	     * OK the segment is to be consumed as chars.
	     */
	    if ((ctxt->sax != NULL) && (!ctxt->disableSAX)) {
		if (areBlanks(ctxt, buf, nbchar, 0)) {
		    if (ctxt->sax->ignorableWhitespace != NULL)
			ctxt->sax->ignorableWhitespace(ctxt->userData,
			                               buf, nbchar);
		} else {
		    if (ctxt->sax->characters != NULL)
			ctxt->sax->characters(ctxt->userData, buf, nbchar);
		    if ((ctxt->sax->characters !=
		         ctxt->sax->ignorableWhitespace) &&
			(*ctxt->space == -1))
			*ctxt->space = -2;
		}
	    }
	    nbchar = 0;
            /* something really bad happened in the SAX callback */
            if (ctxt->instate != XML_PARSER_CONTENT)
                return;
	}
	count++;
	if (count > 50) {
	    GROW;
	    count = 0;
            if (ctxt->instate == XML_PARSER_EOF)
		return;
	}
	NEXTL(l);
	cur = CUR_CHAR(l);
    }
    if (nbchar != 0) {
        buf[nbchar] = 0;
	/*
	 * OK the segment is to be consumed as chars.
	 */
	if ((ctxt->sax != NULL) && (!ctxt->disableSAX)) {
	    if (areBlanks(ctxt, buf, nbchar, 0)) {
		if (ctxt->sax->ignorableWhitespace != NULL)
		    ctxt->sax->ignorableWhitespace(ctxt->userData, buf, nbchar);
	    } else {
		if (ctxt->sax->characters != NULL)
		    ctxt->sax->characters(ctxt->userData, buf, nbchar);
		if ((ctxt->sax->characters != ctxt->sax->ignorableWhitespace) &&
		    (*ctxt->space == -1))
		    *ctxt->space = -2;
	    }
	}
    }
    if ((cur != 0) && (!IS_CHAR(cur))) {
	/* Generate the error and skip the offending character */
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
                          "PCDATA invalid Char value %d\n",
	                  cur);
	NEXTL(l);
    }
}