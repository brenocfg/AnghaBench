#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_7__ {int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,scalar_t__*,int,int) ; 
 int CUR_SCHAR (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  XML_ERR_NAME_TOO_LONG ; 
 int XML_MAX_NAMELEN ; 
 int XML_MAX_NAME_LENGTH ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  nbParseStringName ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__ xmlIsNameChar (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlIsNameStartChar (TYPE_1__*,int) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__ xmlRealloc (scalar_t__*,int) ; 
 scalar_t__* xmlStrndup (scalar_t__*,int) ; 

__attribute__((used)) static xmlChar *
xmlParseStringName(xmlParserCtxtPtr ctxt, const xmlChar** str) {
    xmlChar buf[XML_MAX_NAMELEN + 5];
    const xmlChar *cur = *str;
    int len = 0, l;
    int c;

#ifdef DEBUG
    nbParseStringName++;
#endif

    c = CUR_SCHAR(cur, l);
    if (!xmlIsNameStartChar(ctxt, c)) {
	return(NULL);
    }

    COPY_BUF(l,buf,len,c);
    cur += l;
    c = CUR_SCHAR(cur, l);
    while (xmlIsNameChar(ctxt, c)) {
	COPY_BUF(l,buf,len,c);
	cur += l;
	c = CUR_SCHAR(cur, l);
	if (len >= XML_MAX_NAMELEN) { /* test bigentname.xml */
	    /*
	     * Okay someone managed to make a huge name, so he's ready to pay
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
		if (len + 10 > max) {
		    xmlChar *tmp;

                    if ((len > XML_MAX_NAME_LENGTH) &&
                        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                        xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NCName");
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
		cur += l;
		c = CUR_SCHAR(cur, l);
	    }
	    buffer[len] = 0;
	    *str = cur;
	    return(buffer);
	}
    }
    if ((len > XML_MAX_NAME_LENGTH) &&
        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
        xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NCName");
        return(NULL);
    }
    *str = cur;
    return(xmlStrndup(buf, len));
}