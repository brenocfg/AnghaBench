#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int xmlChar ;
struct TYPE_8__ {scalar_t__ instate; scalar_t__ input; int inSubset; int inputNr; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,int*,int,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 char RAW ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_CHAR_ERROR ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_PE_INTERNAL ; 
 int XML_PARSER_BUFFER_SIZE ; 
 scalar_t__ XML_PARSER_ENTITY_VALUE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  XML_SUBSTITUTE_PEREF ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlFree (int*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 int* xmlParseStringName (TYPE_1__*,int const**) ; 
 scalar_t__ xmlRealloc (int*,int) ; 
 int* xmlStringDecodeEntities (TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

xmlChar *
xmlParseEntityValue(xmlParserCtxtPtr ctxt, xmlChar **orig) {
    xmlChar *buf = NULL;
    int len = 0;
    int size = XML_PARSER_BUFFER_SIZE;
    int c, l;
    xmlChar stop;
    xmlChar *ret = NULL;
    const xmlChar *cur = NULL;
    xmlParserInputPtr input;

    if (RAW == '"') stop = '"';
    else if (RAW == '\'') stop = '\'';
    else {
	xmlFatalErr(ctxt, XML_ERR_ENTITY_NOT_STARTED, NULL);
	return(NULL);
    }
    buf = (xmlChar *) xmlMallocAtomic(size * sizeof(xmlChar));
    if (buf == NULL) {
	xmlErrMemory(ctxt, NULL);
	return(NULL);
    }

    /*
     * The content of the entity definition is copied in a buffer.
     */

    ctxt->instate = XML_PARSER_ENTITY_VALUE;
    input = ctxt->input;
    GROW;
    if (ctxt->instate == XML_PARSER_EOF)
        goto error;
    NEXT;
    c = CUR_CHAR(l);
    /*
     * NOTE: 4.4.5 Included in Literal
     * When a parameter entity reference appears in a literal entity
     * value, ... a single or double quote character in the replacement
     * text is always treated as a normal data character and will not
     * terminate the literal.
     * In practice it means we stop the loop only when back at parsing
     * the initial entity and the quote is found
     */
    while (((IS_CHAR(c)) && ((c != stop) || /* checked */
	    (ctxt->input != input))) && (ctxt->instate != XML_PARSER_EOF)) {
	if (len + 5 >= size) {
	    xmlChar *tmp;

	    size *= 2;
	    tmp = (xmlChar *) xmlRealloc(buf, size * sizeof(xmlChar));
	    if (tmp == NULL) {
		xmlErrMemory(ctxt, NULL);
                goto error;
	    }
	    buf = tmp;
	}
	COPY_BUF(l,buf,len,c);
	NEXTL(l);

	GROW;
	c = CUR_CHAR(l);
	if (c == 0) {
	    GROW;
	    c = CUR_CHAR(l);
	}
    }
    buf[len] = 0;
    if (ctxt->instate == XML_PARSER_EOF)
        goto error;
    if (c != stop) {
        xmlFatalErr(ctxt, XML_ERR_ENTITY_NOT_FINISHED, NULL);
        goto error;
    }
    NEXT;

    /*
     * Raise problem w.r.t. '&' and '%' being used in non-entities
     * reference constructs. Note Charref will be handled in
     * xmlStringDecodeEntities()
     */
    cur = buf;
    while (*cur != 0) { /* non input consuming */
	if ((*cur == '%') || ((*cur == '&') && (cur[1] != '#'))) {
	    xmlChar *name;
	    xmlChar tmp = *cur;
            int nameOk = 0;

	    cur++;
	    name = xmlParseStringName(ctxt, &cur);
            if (name != NULL) {
                nameOk = 1;
                xmlFree(name);
            }
            if ((nameOk == 0) || (*cur != ';')) {
		xmlFatalErrMsgInt(ctxt, XML_ERR_ENTITY_CHAR_ERROR,
	    "EntityValue: '%c' forbidden except for entities references\n",
	                          tmp);
                goto error;
	    }
	    if ((tmp == '%') && (ctxt->inSubset == 1) &&
		(ctxt->inputNr == 1)) {
		xmlFatalErr(ctxt, XML_ERR_ENTITY_PE_INTERNAL, NULL);
                goto error;
	    }
	    if (*cur == 0)
	        break;
	}
	cur++;
    }

    /*
     * Then PEReference entities are substituted.
     *
     * NOTE: 4.4.7 Bypassed
     * When a general entity reference appears in the EntityValue in
     * an entity declaration, it is bypassed and left as is.
     * so XML_SUBSTITUTE_REF is not set here.
     */
    ++ctxt->depth;
    ret = xmlStringDecodeEntities(ctxt, buf, XML_SUBSTITUTE_PEREF,
                                  0, 0, 0);
    --ctxt->depth;
    if (orig != NULL) {
        *orig = buf;
        buf = NULL;
    }

error:
    if (buf != NULL)
        xmlFree(buf);
    return(ret);
}