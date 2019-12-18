#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* xmlParserInputState ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int xmlChar ;
struct TYPE_5__ {int instate; int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,int*,int,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_LITERAL_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_LITERAL_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_NAME_TOO_LONG ; 
 int XML_MAX_NAME_LENGTH ; 
 int XML_PARSER_BUFFER_SIZE ; 
 int XML_PARSER_EOF ; 
 int XML_PARSER_SYSTEM_LITERAL ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (int*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__ xmlRealloc (int*,int) ; 

xmlChar *
xmlParseSystemLiteral(xmlParserCtxtPtr ctxt) {
    xmlChar *buf = NULL;
    int len = 0;
    int size = XML_PARSER_BUFFER_SIZE;
    int cur, l;
    xmlChar stop;
    int state = ctxt->instate;
    int count = 0;

    SHRINK;
    if (RAW == '"') {
        NEXT;
	stop = '"';
    } else if (RAW == '\'') {
        NEXT;
	stop = '\'';
    } else {
	xmlFatalErr(ctxt, XML_ERR_LITERAL_NOT_STARTED, NULL);
	return(NULL);
    }

    buf = (xmlChar *) xmlMallocAtomic(size * sizeof(xmlChar));
    if (buf == NULL) {
        xmlErrMemory(ctxt, NULL);
	return(NULL);
    }
    ctxt->instate = XML_PARSER_SYSTEM_LITERAL;
    cur = CUR_CHAR(l);
    while ((IS_CHAR(cur)) && (cur != stop)) { /* checked */
	if (len + 5 >= size) {
	    xmlChar *tmp;

            if ((size > XML_MAX_NAME_LENGTH) &&
                ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "SystemLiteral");
                xmlFree(buf);
		ctxt->instate = (xmlParserInputState) state;
                return(NULL);
            }
	    size *= 2;
	    tmp = (xmlChar *) xmlRealloc(buf, size * sizeof(xmlChar));
	    if (tmp == NULL) {
	        xmlFree(buf);
		xmlErrMemory(ctxt, NULL);
		ctxt->instate = (xmlParserInputState) state;
		return(NULL);
	    }
	    buf = tmp;
	}
	count++;
	if (count > 50) {
	    GROW;
	    count = 0;
            if (ctxt->instate == XML_PARSER_EOF) {
	        xmlFree(buf);
		return(NULL);
            }
	}
	COPY_BUF(l,buf,len,cur);
	NEXTL(l);
	cur = CUR_CHAR(l);
	if (cur == 0) {
	    GROW;
	    SHRINK;
	    cur = CUR_CHAR(l);
	}
    }
    buf[len] = 0;
    ctxt->instate = (xmlParserInputState) state;
    if (!IS_CHAR(cur)) {
	xmlFatalErr(ctxt, XML_ERR_LITERAL_NOT_FINISHED, NULL);
    } else {
	NEXT;
    }
    return(buf);
}