#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputPtr ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  TYPE_3__* xmlEntityPtr ;
typedef  TYPE_4__* xmlBufferPtr ;
struct TYPE_21__ {int /*<<< orphan*/ * content; } ;
struct TYPE_20__ {scalar_t__ etype; int /*<<< orphan*/ * content; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_18__ {scalar_t__ cur; scalar_t__ end; } ;

/* Variables and functions */
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHAR ; 
 scalar_t__ XML_EXTERNAL_GENERAL_PARSED_ENTITY ; 
 scalar_t__ XML_EXTERNAL_PARAMETER_ENTITY ; 
 int /*<<< orphan*/  XML_PARSER_CHUNK_SIZE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlBufferAdd (TYPE_4__*,scalar_t__,int) ; 
 TYPE_4__* xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (TYPE_4__*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_1__* xmlNewEntityInputStream (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ xmlParserDebugEntities ; 
 int /*<<< orphan*/  xmlPopInput (TYPE_2__*) ; 
 scalar_t__ xmlPushInput (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
xmlLoadEntityContent(xmlParserCtxtPtr ctxt, xmlEntityPtr entity) {
    xmlParserInputPtr input;
    xmlBufferPtr buf;
    int l, c;
    int count = 0;

    if ((ctxt == NULL) || (entity == NULL) ||
        ((entity->etype != XML_EXTERNAL_PARAMETER_ENTITY) &&
	 (entity->etype != XML_EXTERNAL_GENERAL_PARSED_ENTITY)) ||
	(entity->content != NULL)) {
	xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
	            "xmlLoadEntityContent parameter error");
        return(-1);
    }

    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"Reading %s entity content input\n", entity->name);

    buf = xmlBufferCreate();
    if (buf == NULL) {
	xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
	            "xmlLoadEntityContent parameter error");
        return(-1);
    }

    input = xmlNewEntityInputStream(ctxt, entity);
    if (input == NULL) {
	xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
	            "xmlLoadEntityContent input error");
	xmlBufferFree(buf);
        return(-1);
    }

    /*
     * Push the entity as the current input, read char by char
     * saving to the buffer until the end of the entity or an error
     */
    if (xmlPushInput(ctxt, input) < 0) {
        xmlBufferFree(buf);
	return(-1);
    }

    GROW;
    c = CUR_CHAR(l);
    while ((ctxt->input == input) && (ctxt->input->cur < ctxt->input->end) &&
           (IS_CHAR(c))) {
        xmlBufferAdd(buf, ctxt->input->cur, l);
	if (count++ > XML_PARSER_CHUNK_SIZE) {
	    count = 0;
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF) {
                xmlBufferFree(buf);
                return(-1);
            }
	}
	NEXTL(l);
	c = CUR_CHAR(l);
	if (c == 0) {
	    count = 0;
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF) {
                xmlBufferFree(buf);
                return(-1);
            }
	    c = CUR_CHAR(l);
	}
    }

    if ((ctxt->input == input) && (ctxt->input->cur >= ctxt->input->end)) {
        xmlPopInput(ctxt);
    } else if (!IS_CHAR(c)) {
        xmlFatalErrMsgInt(ctxt, XML_ERR_INVALID_CHAR,
                          "xmlLoadEntityContent: invalid char value %d\n",
	                  c);
	xmlBufferFree(buf);
	return(-1);
    }
    entity->content = buf->content;
    buf->content = NULL;
    xmlBufferFree(buf);

    return(0);
}