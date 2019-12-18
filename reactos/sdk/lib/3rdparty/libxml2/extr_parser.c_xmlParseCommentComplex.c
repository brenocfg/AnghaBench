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
typedef  scalar_t__ xmlChar ;
struct TYPE_12__ {int options; scalar_t__ instate; int /*<<< orphan*/  userData; TYPE_2__* sax; int /*<<< orphan*/  disableSAX; TYPE_1__* input; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* comment ) (int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct TYPE_10__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,scalar_t__*,size_t,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_COMMENT_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_BOUNDARY ; 
 int /*<<< orphan*/  XML_ERR_HYPHEN_IN_COMMENT ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHAR ; 
 size_t XML_MAX_TEXT_LENGTH ; 
 size_t XML_PARSER_BUFFER_SIZE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlFatalErrMsgStr (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__ xmlMallocAtomic (size_t) ; 
 scalar_t__ xmlRealloc (scalar_t__*,size_t) ; 

__attribute__((used)) static void
xmlParseCommentComplex(xmlParserCtxtPtr ctxt, xmlChar *buf,
                       size_t len, size_t size) {
    int q, ql;
    int r, rl;
    int cur, l;
    size_t count = 0;
    int inputid;

    inputid = ctxt->input->id;

    if (buf == NULL) {
        len = 0;
	size = XML_PARSER_BUFFER_SIZE;
	buf = (xmlChar *) xmlMallocAtomic(size * sizeof(xmlChar));
	if (buf == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    return;
	}
    }
    GROW;	/* Assure there's enough input data */
    q = CUR_CHAR(ql);
    if (q == 0)
        goto not_terminated;
    if (!IS_CHAR(q)) {
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
                          "xmlParseComment: invalid xmlChar value %d\n",
	                  q);
	xmlFree (buf);
	return;
    }
    NEXTL(ql);
    r = CUR_CHAR(rl);
    if (r == 0)
        goto not_terminated;
    if (!IS_CHAR(r)) {
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
                          "xmlParseComment: invalid xmlChar value %d\n",
	                  q);
	xmlFree (buf);
	return;
    }
    NEXTL(rl);
    cur = CUR_CHAR(l);
    if (cur == 0)
        goto not_terminated;
    while (IS_CHAR(cur) && /* checked */
           ((cur != '>') ||
	    (r != '-') || (q != '-'))) {
	if ((r == '-') && (q == '-')) {
	    xmlFatalErr(ctxt, XML_ERR_HYPHEN_IN_COMMENT, NULL);
	}
        if ((len > XML_MAX_TEXT_LENGTH) &&
            ((ctxt->options & XML_PARSE_HUGE) == 0)) {
            xmlFatalErrMsgStr(ctxt, XML_ERR_COMMENT_NOT_FINISHED,
                         "Comment too big found", NULL);
            xmlFree (buf);
            return;
        }
	if (len + 5 >= size) {
	    xmlChar *new_buf;
            size_t new_size;

	    new_size = size * 2;
	    new_buf = (xmlChar *) xmlRealloc(buf, new_size);
	    if (new_buf == NULL) {
		xmlFree (buf);
		xmlErrMemory(ctxt, NULL);
		return;
	    }
	    buf = new_buf;
            size = new_size;
	}
	COPY_BUF(ql,buf,len,q);
	q = r;
	ql = rl;
	r = cur;
	rl = l;

	count++;
	if (count > 50) {
	    GROW;
	    count = 0;
            if (ctxt->instate == XML_PARSER_EOF) {
		xmlFree(buf);
		return;
            }
	}
	NEXTL(l);
	cur = CUR_CHAR(l);
	if (cur == 0) {
	    SHRINK;
	    GROW;
	    cur = CUR_CHAR(l);
	}
    }
    buf[len] = 0;
    if (cur == 0) {
	xmlFatalErrMsgStr(ctxt, XML_ERR_COMMENT_NOT_FINISHED,
	                     "Comment not terminated \n<!--%.50s\n", buf);
    } else if (!IS_CHAR(cur)) {
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
                          "xmlParseComment: invalid xmlChar value %d\n",
	                  cur);
    } else {
	if (inputid != ctxt->input->id) {
	    xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
		           "Comment doesn't start and stop in the same"
                           " entity\n");
	}
        NEXT;
	if ((ctxt->sax != NULL) && (ctxt->sax->comment != NULL) &&
	    (!ctxt->disableSAX))
	    ctxt->sax->comment(ctxt->userData, buf);
    }
    xmlFree(buf);
    return;
not_terminated:
    xmlFatalErrMsgStr(ctxt, XML_ERR_COMMENT_NOT_FINISHED,
			 "Comment not terminated\n", NULL);
    xmlFree(buf);
    return;
}