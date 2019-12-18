#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_6__ {scalar_t__ instate; int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,scalar_t__*,int,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 int /*<<< orphan*/  XML_ERR_NAME_TOO_LONG ; 
 int XML_MAX_NAMELEN ; 
 int XML_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  XML_PARSER_CHUNK_SIZE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  nbParseNmToken ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__ xmlIsNameChar (TYPE_1__*,int) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__ xmlRealloc (scalar_t__*,int) ; 
 scalar_t__* xmlStrndup (scalar_t__*,int) ; 

xmlChar *
xmlParseNmtoken(xmlParserCtxtPtr ctxt) {
    xmlChar buf[XML_MAX_NAMELEN + 5];
    int len = 0, l;
    int c;
    int count = 0;

#ifdef DEBUG
    nbParseNmToken++;
#endif

    GROW;
    if (ctxt->instate == XML_PARSER_EOF)
        return(NULL);
    c = CUR_CHAR(l);

    while (xmlIsNameChar(ctxt, c)) {
	if (count++ > XML_PARSER_CHUNK_SIZE) {
	    count = 0;
	    GROW;
	}
	COPY_BUF(l,buf,len,c);
	NEXTL(l);
	c = CUR_CHAR(l);
	if (c == 0) {
	    count = 0;
	    GROW;
	    if (ctxt->instate == XML_PARSER_EOF)
		return(NULL);
            c = CUR_CHAR(l);
	}
	if (len >= XML_MAX_NAMELEN) {
	    /*
	     * Okay someone managed to make a huge token, so he's ready to pay
	     * for the processing speed.
	     */
	    xmlChar *buffer;
	    int max = len * 2;

	    buffer = (xmlChar *) xmlMallocAtomic(max * sizeof(xmlChar));
	    if (buffer == NULL) {
	        xmlErrMemory(ctxt, NULL);
		return(NULL);
	    }
	    memcpy(buffer, buf, len);
	    while (xmlIsNameChar(ctxt, c)) {
		if (count++ > XML_PARSER_CHUNK_SIZE) {
		    count = 0;
		    GROW;
                    if (ctxt->instate == XML_PARSER_EOF) {
                        xmlFree(buffer);
                        return(NULL);
                    }
		}
		if (len + 10 > max) {
		    xmlChar *tmp;

                    if ((max > XML_MAX_NAME_LENGTH) &&
                        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                        xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NmToken");
                        xmlFree(buffer);
                        return(NULL);
                    }
		    max *= 2;
		    tmp = (xmlChar *) xmlRealloc(buffer,
			                            max * sizeof(xmlChar));
		    if (tmp == NULL) {
			xmlErrMemory(ctxt, NULL);
			xmlFree(buffer);
			return(NULL);
		    }
		    buffer = tmp;
		}
		COPY_BUF(l,buffer,len,c);
		NEXTL(l);
		c = CUR_CHAR(l);
	    }
	    buffer[len] = 0;
	    return(buffer);
	}
    }
    if (len == 0)
        return(NULL);
    if ((len > XML_MAX_NAME_LENGTH) &&
        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
        xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NmToken");
        return(NULL);
    }
    return(xmlStrndup(buf, len));
}