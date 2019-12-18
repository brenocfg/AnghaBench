#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
struct TYPE_7__ {scalar_t__ instate; TYPE_1__* input; int /*<<< orphan*/  nbChars; } ;
struct TYPE_6__ {int /*<<< orphan*/  cur; int /*<<< orphan*/  col; } ;

/* Variables and functions */
 unsigned int CUR ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (unsigned int) ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHAR ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHARREF ; 
 int /*<<< orphan*/  XML_ERR_INVALID_DEC_CHARREF ; 
 int /*<<< orphan*/  XML_ERR_INVALID_HEX_CHARREF ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_2__*,int /*<<< orphan*/ ,char*,unsigned int) ; 

int
xmlParseCharRef(xmlParserCtxtPtr ctxt) {
    unsigned int val = 0;
    int count = 0;
    unsigned int outofrange = 0;

    /*
     * Using RAW/CUR/NEXT is okay since we are working on ASCII range here
     */
    if ((RAW == '&') && (NXT(1) == '#') &&
        (NXT(2) == 'x')) {
	SKIP(3);
	GROW;
	while (RAW != ';') { /* loop blocked by count */
	    if (count++ > 20) {
		count = 0;
		GROW;
                if (ctxt->instate == XML_PARSER_EOF)
                    return(0);
	    }
	    if ((RAW >= '0') && (RAW <= '9'))
	        val = val * 16 + (CUR - '0');
	    else if ((RAW >= 'a') && (RAW <= 'f') && (count < 20))
	        val = val * 16 + (CUR - 'a') + 10;
	    else if ((RAW >= 'A') && (RAW <= 'F') && (count < 20))
	        val = val * 16 + (CUR - 'A') + 10;
	    else {
		xmlFatalErr(ctxt, XML_ERR_INVALID_HEX_CHARREF, NULL);
		val = 0;
		break;
	    }
	    if (val > 0x10FFFF)
	        outofrange = val;

	    NEXT;
	    count++;
	}
	if (RAW == ';') {
	    /* on purpose to avoid reentrancy problems with NEXT and SKIP */
	    ctxt->input->col++;
	    ctxt->nbChars ++;
	    ctxt->input->cur++;
	}
    } else if  ((RAW == '&') && (NXT(1) == '#')) {
	SKIP(2);
	GROW;
	while (RAW != ';') { /* loop blocked by count */
	    if (count++ > 20) {
		count = 0;
		GROW;
                if (ctxt->instate == XML_PARSER_EOF)
                    return(0);
	    }
	    if ((RAW >= '0') && (RAW <= '9'))
	        val = val * 10 + (CUR - '0');
	    else {
		xmlFatalErr(ctxt, XML_ERR_INVALID_DEC_CHARREF, NULL);
		val = 0;
		break;
	    }
	    if (val > 0x10FFFF)
	        outofrange = val;

	    NEXT;
	    count++;
	}
	if (RAW == ';') {
	    /* on purpose to avoid reentrancy problems with NEXT and SKIP */
	    ctxt->input->col++;
	    ctxt->nbChars ++;
	    ctxt->input->cur++;
	}
    } else {
        xmlFatalErr(ctxt, XML_ERR_INVALID_CHARREF, NULL);
    }

    /*
     * [ WFC: Legal Character ]
     * Characters referred to using character references must match the
     * production for Char.
     */
    if ((IS_CHAR(val) && (outofrange == 0))) {
        return(val);
    } else {
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
                          "xmlParseCharRef: invalid xmlChar value %d\n",
	                  val);
    }
    return(0);
}