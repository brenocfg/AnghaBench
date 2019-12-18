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
struct TYPE_8__ {scalar_t__ instate; int options; int /*<<< orphan*/  userData; TYPE_1__* sax; int /*<<< orphan*/  disableSAX; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* characters ) (int /*<<< orphan*/ ,scalar_t__*,int) ;int /*<<< orphan*/  (* cdataBlock ) (int /*<<< orphan*/ ,scalar_t__*,int) ;} ;

/* Variables and functions */
 scalar_t__ CMP9 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  COPY_BUF (int,scalar_t__*,int,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int /*<<< orphan*/  XML_ERR_CDATA_NOT_FINISHED ; 
 int XML_MAX_TEXT_LENGTH ; 
 int XML_PARSER_BUFFER_SIZE ; 
 scalar_t__ XML_PARSER_CDATA_SECTION ; 
 void* XML_PARSER_CONTENT ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsgStr (TYPE_2__*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__ xmlRealloc (scalar_t__*,int) ; 

void
xmlParseCDSect(xmlParserCtxtPtr ctxt) {
    xmlChar *buf = NULL;
    int len = 0;
    int size = XML_PARSER_BUFFER_SIZE;
    int r, rl;
    int	s, sl;
    int cur, l;
    int count = 0;

    /* Check 2.6.0 was NXT(0) not RAW */
    if (CMP9(CUR_PTR, '<', '!', '[', 'C', 'D', 'A', 'T', 'A', '[')) {
	SKIP(9);
    } else
        return;

    ctxt->instate = XML_PARSER_CDATA_SECTION;
    r = CUR_CHAR(rl);
    if (!IS_CHAR(r)) {
	xmlFatalErr(ctxt, XML_ERR_CDATA_NOT_FINISHED, NULL);
	ctxt->instate = XML_PARSER_CONTENT;
        return;
    }
    NEXTL(rl);
    s = CUR_CHAR(sl);
    if (!IS_CHAR(s)) {
	xmlFatalErr(ctxt, XML_ERR_CDATA_NOT_FINISHED, NULL);
	ctxt->instate = XML_PARSER_CONTENT;
        return;
    }
    NEXTL(sl);
    cur = CUR_CHAR(l);
    buf = (xmlChar *) xmlMallocAtomic(size * sizeof(xmlChar));
    if (buf == NULL) {
	xmlErrMemory(ctxt, NULL);
	return;
    }
    while (IS_CHAR(cur) &&
           ((r != ']') || (s != ']') || (cur != '>'))) {
	if (len + 5 >= size) {
	    xmlChar *tmp;

            if ((size > XML_MAX_TEXT_LENGTH) &&
                ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                xmlFatalErrMsgStr(ctxt, XML_ERR_CDATA_NOT_FINISHED,
                             "CData section too big found", NULL);
                xmlFree (buf);
                return;
            }
	    tmp = (xmlChar *) xmlRealloc(buf, size * 2 * sizeof(xmlChar));
	    if (tmp == NULL) {
	        xmlFree(buf);
		xmlErrMemory(ctxt, NULL);
		return;
	    }
	    buf = tmp;
	    size *= 2;
	}
	COPY_BUF(rl,buf,len,r);
	r = s;
	rl = sl;
	s = cur;
	sl = l;
	count++;
	if (count > 50) {
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF) {
		xmlFree(buf);
		return;
            }
	    count = 0;
	}
	NEXTL(l);
	cur = CUR_CHAR(l);
    }
    buf[len] = 0;
    ctxt->instate = XML_PARSER_CONTENT;
    if (cur != '>') {
	xmlFatalErrMsgStr(ctxt, XML_ERR_CDATA_NOT_FINISHED,
	                     "CData section not finished\n%.50s\n", buf);
	xmlFree(buf);
        return;
    }
    NEXTL(l);

    /*
     * OK the buffer is to be consumed as cdata.
     */
    if ((ctxt->sax != NULL) && (!ctxt->disableSAX)) {
	if (ctxt->sax->cdataBlock != NULL)
	    ctxt->sax->cdataBlock(ctxt->userData, buf, len);
	else if (ctxt->sax->characters != NULL)
	    ctxt->sax->characters(ctxt->userData, buf, len);
    }
    xmlFree(buf);
}