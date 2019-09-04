#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xmlParserCtxtPtr ;
typedef  char xmlChar ;

/* Variables and functions */
 char CUR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_ENCODING_NAME ; 
 int /*<<< orphan*/  xmlErrMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 scalar_t__ xmlRealloc (char*,int) ; 

xmlChar *
xmlParseEncName(xmlParserCtxtPtr ctxt) {
    xmlChar *buf = NULL;
    int len = 0;
    int size = 10;
    xmlChar cur;

    cur = CUR;
    if (((cur >= 'a') && (cur <= 'z')) ||
        ((cur >= 'A') && (cur <= 'Z'))) {
	buf = (xmlChar *) xmlMallocAtomic(size * sizeof(xmlChar));
	if (buf == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    return(NULL);
	}

	buf[len++] = cur;
	NEXT;
	cur = CUR;
	while (((cur >= 'a') && (cur <= 'z')) ||
	       ((cur >= 'A') && (cur <= 'Z')) ||
	       ((cur >= '0') && (cur <= '9')) ||
	       (cur == '.') || (cur == '_') ||
	       (cur == '-')) {
	    if (len + 1 >= size) {
	        xmlChar *tmp;

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
	    NEXT;
	    cur = CUR;
	    if (cur == 0) {
	        SHRINK;
		GROW;
		cur = CUR;
	    }
        }
	buf[len] = 0;
    } else {
	xmlFatalErr(ctxt, XML_ERR_ENCODING_NAME, NULL);
    }
    return(buf);
}