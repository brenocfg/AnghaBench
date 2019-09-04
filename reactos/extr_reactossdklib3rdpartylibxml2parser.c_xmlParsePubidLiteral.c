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
typedef  int /*<<< orphan*/  xmlParserInputState ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  char xmlChar ;
struct TYPE_5__ {int options; int /*<<< orphan*/  instate; } ;

/* Variables and functions */
 char CUR ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_PUBIDCHAR_CH (char) ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_LITERAL_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_LITERAL_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_NAME_TOO_LONG ; 
 int XML_MAX_NAME_LENGTH ; 
 int XML_PARSER_BUFFER_SIZE ; 
 int /*<<< orphan*/  XML_PARSER_EOF ; 
 int /*<<< orphan*/  XML_PARSER_PUBLIC_LITERAL ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__ xmlRealloc (char*,int) ; 

xmlChar *
xmlParsePubidLiteral(xmlParserCtxtPtr ctxt) {
    xmlChar *buf = NULL;
    int len = 0;
    int size = XML_PARSER_BUFFER_SIZE;
    xmlChar cur;
    xmlChar stop;
    int count = 0;
    xmlParserInputState oldstate = ctxt->instate;

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
    ctxt->instate = XML_PARSER_PUBLIC_LITERAL;
    cur = CUR;
    while ((IS_PUBIDCHAR_CH(cur)) && (cur != stop)) { /* checked */
	if (len + 1 >= size) {
	    xmlChar *tmp;

            if ((size > XML_MAX_NAME_LENGTH) &&
                ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "Public ID");
                xmlFree(buf);
                return(NULL);
            }
	    size *= 2;
	    tmp = (xmlChar *) xmlRealloc(buf, size * sizeof(xmlChar));
	    if (tmp == NULL) {
		xmlErrMemory(ctxt, NULL);
		xmlFree(buf);
		return(NULL);
	    }
	    buf = tmp;
	}
	buf[len++] = cur;
	count++;
	if (count > 50) {
	    GROW;
	    count = 0;
            if (ctxt->instate == XML_PARSER_EOF) {
		xmlFree(buf);
		return(NULL);
            }
	}
	NEXT;
	cur = CUR;
	if (cur == 0) {
	    GROW;
	    SHRINK;
	    cur = CUR;
	}
    }
    buf[len] = 0;
    if (cur != stop) {
	xmlFatalErr(ctxt, XML_ERR_LITERAL_NOT_FINISHED, NULL);
    } else {
	NEXT;
    }
    ctxt->instate = oldstate;
    return(buf);
}