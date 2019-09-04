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
 scalar_t__ IS_CHAR (unsigned int) ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHAR ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHARREF ; 
 int /*<<< orphan*/  XML_ERR_INVALID_DEC_CHARREF ; 
 int /*<<< orphan*/  XML_ERR_INVALID_HEX_CHARREF ; 
 int /*<<< orphan*/  xmlFatalErr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int
xmlParseStringCharRef(xmlParserCtxtPtr ctxt, const xmlChar **str) {
    const xmlChar *ptr;
    xmlChar cur;
    unsigned int val = 0;
    unsigned int outofrange = 0;

    if ((str == NULL) || (*str == NULL)) return(0);
    ptr = *str;
    cur = *ptr;
    if ((cur == '&') && (ptr[1] == '#') && (ptr[2] == 'x')) {
	ptr += 3;
	cur = *ptr;
	while (cur != ';') { /* Non input consuming loop */
	    if ((cur >= '0') && (cur <= '9'))
	        val = val * 16 + (cur - '0');
	    else if ((cur >= 'a') && (cur <= 'f'))
	        val = val * 16 + (cur - 'a') + 10;
	    else if ((cur >= 'A') && (cur <= 'F'))
	        val = val * 16 + (cur - 'A') + 10;
	    else {
		xmlFatalErr(ctxt, XML_ERR_INVALID_HEX_CHARREF, NULL);
		val = 0;
		break;
	    }
	    if (val > 0x10FFFF)
	        outofrange = val;

	    ptr++;
	    cur = *ptr;
	}
	if (cur == ';')
	    ptr++;
    } else if  ((cur == '&') && (ptr[1] == '#')){
	ptr += 2;
	cur = *ptr;
	while (cur != ';') { /* Non input consuming loops */
	    if ((cur >= '0') && (cur <= '9'))
	        val = val * 10 + (cur - '0');
	    else {
		xmlFatalErr(ctxt, XML_ERR_INVALID_DEC_CHARREF, NULL);
		val = 0;
		break;
	    }
	    if (val > 0x10FFFF)
	        outofrange = val;

	    ptr++;
	    cur = *ptr;
	}
	if (cur == ';')
	    ptr++;
    } else {
	xmlFatalErr(ctxt, XML_ERR_INVALID_CHARREF, NULL);
	return(0);
    }
    *str = ptr;

    /*
     * [ WFC: Legal Character ]
     * Characters referred to using character references must match the
     * production for Char.
     */
    if ((IS_CHAR(val) && (outofrange == 0))) {
        return(val);
    } else {
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
			  "xmlParseStringCharRef: invalid xmlChar value %d\n",
			  val);
    }
    return(0);
}