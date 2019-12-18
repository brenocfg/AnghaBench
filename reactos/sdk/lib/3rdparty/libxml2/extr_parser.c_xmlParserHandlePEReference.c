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
struct TYPE_5__ {int instate; int inputNr; int /*<<< orphan*/  external; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_BLANK_CH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXT (int) ; 
 int /*<<< orphan*/  XML_ERR_PEREF_AT_EOF ; 
 int /*<<< orphan*/  XML_ERR_PEREF_IN_EPILOG ; 
 int /*<<< orphan*/  XML_ERR_PEREF_IN_PROLOG ; 
#define  XML_PARSER_ATTRIBUTE_VALUE 145 
#define  XML_PARSER_CDATA_SECTION 144 
#define  XML_PARSER_COMMENT 143 
#define  XML_PARSER_CONTENT 142 
#define  XML_PARSER_DTD 141 
#define  XML_PARSER_END_TAG 140 
#define  XML_PARSER_ENTITY_DECL 139 
#define  XML_PARSER_ENTITY_VALUE 138 
#define  XML_PARSER_EOF 137 
#define  XML_PARSER_EPILOG 136 
#define  XML_PARSER_IGNORE 135 
#define  XML_PARSER_MISC 134 
#define  XML_PARSER_PI 133 
#define  XML_PARSER_PROLOG 132 
#define  XML_PARSER_PUBLIC_LITERAL 131 
#define  XML_PARSER_START 130 
#define  XML_PARSER_START_TAG 129 
#define  XML_PARSER_SYSTEM_LITERAL 128 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlParsePEReference (TYPE_1__*) ; 

void
xmlParserHandlePEReference(xmlParserCtxtPtr ctxt) {
    switch(ctxt->instate) {
	case XML_PARSER_CDATA_SECTION:
	    return;
        case XML_PARSER_COMMENT:
	    return;
	case XML_PARSER_START_TAG:
	    return;
	case XML_PARSER_END_TAG:
	    return;
        case XML_PARSER_EOF:
	    xmlFatalErr(ctxt, XML_ERR_PEREF_AT_EOF, NULL);
	    return;
        case XML_PARSER_PROLOG:
	case XML_PARSER_START:
	case XML_PARSER_MISC:
	    xmlFatalErr(ctxt, XML_ERR_PEREF_IN_PROLOG, NULL);
	    return;
	case XML_PARSER_ENTITY_DECL:
        case XML_PARSER_CONTENT:
        case XML_PARSER_ATTRIBUTE_VALUE:
        case XML_PARSER_PI:
	case XML_PARSER_SYSTEM_LITERAL:
	case XML_PARSER_PUBLIC_LITERAL:
	    /* we just ignore it there */
	    return;
        case XML_PARSER_EPILOG:
	    xmlFatalErr(ctxt, XML_ERR_PEREF_IN_EPILOG, NULL);
	    return;
	case XML_PARSER_ENTITY_VALUE:
	    /*
	     * NOTE: in the case of entity values, we don't do the
	     *       substitution here since we need the literal
	     *       entity value to be able to save the internal
	     *       subset of the document.
	     *       This will be handled by xmlStringDecodeEntities
	     */
	    return;
        case XML_PARSER_DTD:
	    /*
	     * [WFC: Well-Formedness Constraint: PEs in Internal Subset]
	     * In the internal DTD subset, parameter-entity references
	     * can occur only where markup declarations can occur, not
	     * within markup declarations.
	     * In that case this is handled in xmlParseMarkupDecl
	     */
	    if ((ctxt->external == 0) && (ctxt->inputNr == 1))
		return;
	    if (IS_BLANK_CH(NXT(1)) || NXT(1) == 0)
		return;
            break;
        case XML_PARSER_IGNORE:
            return;
    }

    xmlParsePEReference(ctxt);
}