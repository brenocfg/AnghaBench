#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_10__ {scalar_t__ instate; scalar_t__ external; int inputNr; } ;

/* Variables and functions */
 char CUR ; 
 int /*<<< orphan*/  GROW ; 
 char NXT (int) ; 
 char RAW ; 
 scalar_t__ XML_PARSER_DTD ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlParseAttributeListDecl (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParseComment (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParseConditionalSections (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParseElementDecl (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParseEntityDecl (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParseNotationDecl (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlParsePI (TYPE_1__*) ; 

void
xmlParseMarkupDecl(xmlParserCtxtPtr ctxt) {
    GROW;
    if (CUR == '<') {
        if (NXT(1) == '!') {
	    switch (NXT(2)) {
	        case 'E':
		    if (NXT(3) == 'L')
			xmlParseElementDecl(ctxt);
		    else if (NXT(3) == 'N')
			xmlParseEntityDecl(ctxt);
		    break;
	        case 'A':
		    xmlParseAttributeListDecl(ctxt);
		    break;
	        case 'N':
		    xmlParseNotationDecl(ctxt);
		    break;
	        case '-':
		    xmlParseComment(ctxt);
		    break;
		default:
		    /* there is an error but it will be detected later */
		    break;
	    }
	} else if (NXT(1) == '?') {
	    xmlParsePI(ctxt);
	}
    }

    /*
     * detect requirement to exit there and act accordingly
     * and avoid having instate overriden later on
     */
    if (ctxt->instate == XML_PARSER_EOF)
        return;

    /*
     * Conditional sections are allowed from entities included
     * by PE References in the internal subset.
     */
    if ((ctxt->external == 0) && (ctxt->inputNr > 1)) {
        if ((RAW == '<') && (NXT(1) == '!') && (NXT(2) == '[')) {
	    xmlParseConditionalSections(ctxt);
	}
    }

    ctxt->instate = XML_PARSER_DTD;
}