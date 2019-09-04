#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int xmlParserErrors ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_4__ {int disableSAX; scalar_t__ instate; int errNo; scalar_t__ recovery; scalar_t__ wellFormed; } ;

/* Variables and functions */
#define  XML_ERR_ATTLIST_NOT_FINISHED 184 
#define  XML_ERR_ATTLIST_NOT_STARTED 183 
#define  XML_ERR_ATTRIBUTE_NOT_STARTED 182 
#define  XML_ERR_CONDSEC_INVALID 181 
#define  XML_ERR_CONDSEC_INVALID_KEYWORD 180 
#define  XML_ERR_CONDSEC_NOT_FINISHED 179 
#define  XML_ERR_DOCTYPE_NOT_FINISHED 178 
#define  XML_ERR_DOCUMENT_EMPTY 177 
#define  XML_ERR_DOCUMENT_END 176 
#define  XML_ERR_ELEMCONTENT_NOT_FINISHED 175 
#define  XML_ERR_ELEMCONTENT_NOT_STARTED 174 
#define  XML_ERR_ENCODING_NAME 173 
#define  XML_ERR_ENTITYREF_SEMICOL_MISSING 172 
#define  XML_ERR_ENTITY_LOOP 171 
#define  XML_ERR_ENTITY_NOT_FINISHED 170 
#define  XML_ERR_ENTITY_NOT_STARTED 169 
#define  XML_ERR_ENTITY_PE_INTERNAL 168 
#define  XML_ERR_EQUAL_REQUIRED 167 
#define  XML_ERR_EXTRA_CONTENT 166 
#define  XML_ERR_EXT_ENTITY_STANDALONE 165 
#define  XML_ERR_EXT_SUBSET_NOT_FINISHED 164 
 int /*<<< orphan*/  XML_ERR_FATAL ; 
#define  XML_ERR_GT_REQUIRED 163 
#define  XML_ERR_HYPHEN_IN_COMMENT 162 
#define  XML_ERR_INTERNAL_ERROR 161 
#define  XML_ERR_INVALID_CHARREF 160 
#define  XML_ERR_INVALID_DEC_CHARREF 159 
#define  XML_ERR_INVALID_HEX_CHARREF 158 
#define  XML_ERR_LITERAL_NOT_FINISHED 157 
#define  XML_ERR_LITERAL_NOT_STARTED 156 
#define  XML_ERR_LTSLASH_REQUIRED 155 
#define  XML_ERR_LT_IN_ATTRIBUTE 154 
#define  XML_ERR_MISPLACED_CDATA_END 153 
#define  XML_ERR_MIXED_NOT_STARTED 152 
#define  XML_ERR_NAME_TOO_LONG 151 
#define  XML_ERR_NMTOKEN_REQUIRED 150 
#define  XML_ERR_NOTATION_NOT_FINISHED 149 
#define  XML_ERR_NOTATION_NOT_STARTED 148 
#define  XML_ERR_NOT_WELL_BALANCED 147 
#define  XML_ERR_PCDATA_REQUIRED 146 
#define  XML_ERR_PEREF_AT_EOF 145 
#define  XML_ERR_PEREF_IN_EPILOG 144 
#define  XML_ERR_PEREF_IN_INT_SUBSET 143 
#define  XML_ERR_PEREF_IN_PROLOG 142 
#define  XML_ERR_PEREF_NO_NAME 141 
#define  XML_ERR_PEREF_SEMICOL_MISSING 140 
#define  XML_ERR_PI_NOT_STARTED 139 
#define  XML_ERR_PUBID_REQUIRED 138 
#define  XML_ERR_RESERVED_XML_NAME 137 
#define  XML_ERR_STANDALONE_VALUE 136 
#define  XML_ERR_STRING_NOT_CLOSED 135 
#define  XML_ERR_STRING_NOT_STARTED 134 
#define  XML_ERR_URI_FRAGMENT 133 
#define  XML_ERR_URI_REQUIRED 132 
#define  XML_ERR_VALUE_REQUIRED 131 
#define  XML_ERR_VERSION_MISSING 130 
#define  XML_ERR_XMLDECL_NOT_FINISHED 129 
#define  XML_ERR_XMLDECL_NOT_STARTED 128 
 int /*<<< orphan*/  XML_FROM_PARSER ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  __xmlRaiseError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void
xmlFatalErr(xmlParserCtxtPtr ctxt, xmlParserErrors error, const char *info)
{
    const char *errmsg;

    if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    switch (error) {
        case XML_ERR_INVALID_HEX_CHARREF:
            errmsg = "CharRef: invalid hexadecimal value";
            break;
        case XML_ERR_INVALID_DEC_CHARREF:
            errmsg = "CharRef: invalid decimal value";
            break;
        case XML_ERR_INVALID_CHARREF:
            errmsg = "CharRef: invalid value";
            break;
        case XML_ERR_INTERNAL_ERROR:
            errmsg = "internal error";
            break;
        case XML_ERR_PEREF_AT_EOF:
            errmsg = "PEReference at end of document";
            break;
        case XML_ERR_PEREF_IN_PROLOG:
            errmsg = "PEReference in prolog";
            break;
        case XML_ERR_PEREF_IN_EPILOG:
            errmsg = "PEReference in epilog";
            break;
        case XML_ERR_PEREF_NO_NAME:
            errmsg = "PEReference: no name";
            break;
        case XML_ERR_PEREF_SEMICOL_MISSING:
            errmsg = "PEReference: expecting ';'";
            break;
        case XML_ERR_ENTITY_LOOP:
            errmsg = "Detected an entity reference loop";
            break;
        case XML_ERR_ENTITY_NOT_STARTED:
            errmsg = "EntityValue: \" or ' expected";
            break;
        case XML_ERR_ENTITY_PE_INTERNAL:
            errmsg = "PEReferences forbidden in internal subset";
            break;
        case XML_ERR_ENTITY_NOT_FINISHED:
            errmsg = "EntityValue: \" or ' expected";
            break;
        case XML_ERR_ATTRIBUTE_NOT_STARTED:
            errmsg = "AttValue: \" or ' expected";
            break;
        case XML_ERR_LT_IN_ATTRIBUTE:
            errmsg = "Unescaped '<' not allowed in attributes values";
            break;
        case XML_ERR_LITERAL_NOT_STARTED:
            errmsg = "SystemLiteral \" or ' expected";
            break;
        case XML_ERR_LITERAL_NOT_FINISHED:
            errmsg = "Unfinished System or Public ID \" or ' expected";
            break;
        case XML_ERR_MISPLACED_CDATA_END:
            errmsg = "Sequence ']]>' not allowed in content";
            break;
        case XML_ERR_URI_REQUIRED:
            errmsg = "SYSTEM or PUBLIC, the URI is missing";
            break;
        case XML_ERR_PUBID_REQUIRED:
            errmsg = "PUBLIC, the Public Identifier is missing";
            break;
        case XML_ERR_HYPHEN_IN_COMMENT:
            errmsg = "Comment must not contain '--' (double-hyphen)";
            break;
        case XML_ERR_PI_NOT_STARTED:
            errmsg = "xmlParsePI : no target name";
            break;
        case XML_ERR_RESERVED_XML_NAME:
            errmsg = "Invalid PI name";
            break;
        case XML_ERR_NOTATION_NOT_STARTED:
            errmsg = "NOTATION: Name expected here";
            break;
        case XML_ERR_NOTATION_NOT_FINISHED:
            errmsg = "'>' required to close NOTATION declaration";
            break;
        case XML_ERR_VALUE_REQUIRED:
            errmsg = "Entity value required";
            break;
        case XML_ERR_URI_FRAGMENT:
            errmsg = "Fragment not allowed";
            break;
        case XML_ERR_ATTLIST_NOT_STARTED:
            errmsg = "'(' required to start ATTLIST enumeration";
            break;
        case XML_ERR_NMTOKEN_REQUIRED:
            errmsg = "NmToken expected in ATTLIST enumeration";
            break;
        case XML_ERR_ATTLIST_NOT_FINISHED:
            errmsg = "')' required to finish ATTLIST enumeration";
            break;
        case XML_ERR_MIXED_NOT_STARTED:
            errmsg = "MixedContentDecl : '|' or ')*' expected";
            break;
        case XML_ERR_PCDATA_REQUIRED:
            errmsg = "MixedContentDecl : '#PCDATA' expected";
            break;
        case XML_ERR_ELEMCONTENT_NOT_STARTED:
            errmsg = "ContentDecl : Name or '(' expected";
            break;
        case XML_ERR_ELEMCONTENT_NOT_FINISHED:
            errmsg = "ContentDecl : ',' '|' or ')' expected";
            break;
        case XML_ERR_PEREF_IN_INT_SUBSET:
            errmsg =
                "PEReference: forbidden within markup decl in internal subset";
            break;
        case XML_ERR_GT_REQUIRED:
            errmsg = "expected '>'";
            break;
        case XML_ERR_CONDSEC_INVALID:
            errmsg = "XML conditional section '[' expected";
            break;
        case XML_ERR_EXT_SUBSET_NOT_FINISHED:
            errmsg = "Content error in the external subset";
            break;
        case XML_ERR_CONDSEC_INVALID_KEYWORD:
            errmsg =
                "conditional section INCLUDE or IGNORE keyword expected";
            break;
        case XML_ERR_CONDSEC_NOT_FINISHED:
            errmsg = "XML conditional section not closed";
            break;
        case XML_ERR_XMLDECL_NOT_STARTED:
            errmsg = "Text declaration '<?xml' required";
            break;
        case XML_ERR_XMLDECL_NOT_FINISHED:
            errmsg = "parsing XML declaration: '?>' expected";
            break;
        case XML_ERR_EXT_ENTITY_STANDALONE:
            errmsg = "external parsed entities cannot be standalone";
            break;
        case XML_ERR_ENTITYREF_SEMICOL_MISSING:
            errmsg = "EntityRef: expecting ';'";
            break;
        case XML_ERR_DOCTYPE_NOT_FINISHED:
            errmsg = "DOCTYPE improperly terminated";
            break;
        case XML_ERR_LTSLASH_REQUIRED:
            errmsg = "EndTag: '</' not found";
            break;
        case XML_ERR_EQUAL_REQUIRED:
            errmsg = "expected '='";
            break;
        case XML_ERR_STRING_NOT_CLOSED:
            errmsg = "String not closed expecting \" or '";
            break;
        case XML_ERR_STRING_NOT_STARTED:
            errmsg = "String not started expecting ' or \"";
            break;
        case XML_ERR_ENCODING_NAME:
            errmsg = "Invalid XML encoding name";
            break;
        case XML_ERR_STANDALONE_VALUE:
            errmsg = "standalone accepts only 'yes' or 'no'";
            break;
        case XML_ERR_DOCUMENT_EMPTY:
            errmsg = "Document is empty";
            break;
        case XML_ERR_DOCUMENT_END:
            errmsg = "Extra content at the end of the document";
            break;
        case XML_ERR_NOT_WELL_BALANCED:
            errmsg = "chunk is not well balanced";
            break;
        case XML_ERR_EXTRA_CONTENT:
            errmsg = "extra content at the end of well balanced chunk";
            break;
        case XML_ERR_VERSION_MISSING:
            errmsg = "Malformed declaration expecting version";
            break;
        case XML_ERR_NAME_TOO_LONG:
            errmsg = "Name too long use XML_PARSE_HUGE option";
            break;
#if 0
        case:
            errmsg = "";
            break;
#endif
        default:
            errmsg = "Unregistered error message";
    }
    if (ctxt != NULL)
	ctxt->errNo = error;
    if (info == NULL) {
        __xmlRaiseError(NULL, NULL, NULL, ctxt, NULL, XML_FROM_PARSER, error,
                        XML_ERR_FATAL, NULL, 0, info, NULL, NULL, 0, 0, "%s\n",
                        errmsg);
    } else {
        __xmlRaiseError(NULL, NULL, NULL, ctxt, NULL, XML_FROM_PARSER, error,
                        XML_ERR_FATAL, NULL, 0, info, NULL, NULL, 0, 0, "%s: %s\n",
                        errmsg, info);
    }
    if (ctxt != NULL) {
	ctxt->wellFormed = 0;
	if (ctxt->recovery == 0)
	    ctxt->disableSAX = 1;
    }
}