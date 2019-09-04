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
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_5__ {scalar_t__ instate; } ;

/* Variables and functions */
 scalar_t__ CMP4 (int /*<<< orphan*/ ,char,char,char,char) ; 
 int /*<<< orphan*/  CUR ; 
 int /*<<< orphan*/  CUR_PTR ; 
 scalar_t__ IS_BLANK_CH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT ; 
 char NXT (int) ; 
 char RAW ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlParseComment (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParsePI (TYPE_1__*) ; 

void
xmlParseMisc(xmlParserCtxtPtr ctxt) {
    while ((ctxt->instate != XML_PARSER_EOF) &&
           (((RAW == '<') && (NXT(1) == '?')) ||
            (CMP4(CUR_PTR, '<', '!', '-', '-')) ||
            IS_BLANK_CH(CUR))) {
        if ((RAW == '<') && (NXT(1) == '?')) {
	    xmlParsePI(ctxt);
	} else if (IS_BLANK_CH(CUR)) {
	    NEXT;
	} else
	    xmlParseComment(ctxt);
    }
}