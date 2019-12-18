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

/* Variables and functions */
 scalar_t__ CMP10 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_ERR_EQUAL_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_STANDALONE_VALUE ; 
 int /*<<< orphan*/  XML_ERR_STRING_NOT_CLOSED ; 
 int /*<<< orphan*/  XML_ERR_STRING_NOT_STARTED ; 
 int /*<<< orphan*/  xmlFatalErr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xmlParseSDDecl(xmlParserCtxtPtr ctxt) {
    int standalone = -2;

    SKIP_BLANKS;
    if (CMP10(CUR_PTR, 's', 't', 'a', 'n', 'd', 'a', 'l', 'o', 'n', 'e')) {
	SKIP(10);
        SKIP_BLANKS;
	if (RAW != '=') {
	    xmlFatalErr(ctxt, XML_ERR_EQUAL_REQUIRED, NULL);
	    return(standalone);
        }
	NEXT;
	SKIP_BLANKS;
        if (RAW == '\''){
	    NEXT;
	    if ((RAW == 'n') && (NXT(1) == 'o')) {
	        standalone = 0;
                SKIP(2);
	    } else if ((RAW == 'y') && (NXT(1) == 'e') &&
	               (NXT(2) == 's')) {
	        standalone = 1;
		SKIP(3);
            } else {
		xmlFatalErr(ctxt, XML_ERR_STANDALONE_VALUE, NULL);
	    }
	    if (RAW != '\'') {
		xmlFatalErr(ctxt, XML_ERR_STRING_NOT_CLOSED, NULL);
	    } else
	        NEXT;
	} else if (RAW == '"'){
	    NEXT;
	    if ((RAW == 'n') && (NXT(1) == 'o')) {
	        standalone = 0;
		SKIP(2);
	    } else if ((RAW == 'y') && (NXT(1) == 'e') &&
	               (NXT(2) == 's')) {
	        standalone = 1;
                SKIP(3);
            } else {
		xmlFatalErr(ctxt, XML_ERR_STANDALONE_VALUE, NULL);
	    }
	    if (RAW != '"') {
		xmlFatalErr(ctxt, XML_ERR_STRING_NOT_CLOSED, NULL);
	    } else
	        NEXT;
	} else {
	    xmlFatalErr(ctxt, XML_ERR_STRING_NOT_STARTED, NULL);
        }
    }
    return(standalone);
}