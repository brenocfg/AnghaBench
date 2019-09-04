#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  TYPE_2__* xmlEntityPtr ;
typedef  int xmlChar ;
struct TYPE_19__ {int checked; scalar_t__ etype; int* content; int* name; } ;
struct TYPE_18__ {int depth; int options; int nbentities; scalar_t__ validate; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,int*,size_t,int) ; 
 int CUR_SCHAR (int const*,int) ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_LOOP ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_PROCESSING ; 
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 scalar_t__ XML_INTERNAL_PREDEFINED_ENTITY ; 
 size_t XML_PARSER_BIG_BUFFER_SIZE ; 
 size_t XML_PARSER_BUFFER_SIZE ; 
 int XML_PARSE_DTDVALID ; 
 int XML_PARSE_HUGE ; 
 int XML_PARSE_NOENT ; 
 int XML_SUBSTITUTE_PEREF ; 
 int XML_SUBSTITUTE_REF ; 
 int /*<<< orphan*/  growBuffer (int*,size_t) ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (int*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int const*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlLoadEntityContent (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ xmlMallocAtomic (size_t) ; 
 int xmlParseStringCharRef (TYPE_1__*,int const**) ; 
 TYPE_2__* xmlParseStringEntityRef (TYPE_1__*,int const**) ; 
 TYPE_2__* xmlParseStringPEReference (TYPE_1__*,int const**) ; 
 scalar_t__ xmlParserDebugEntities ; 
 scalar_t__ xmlParserEntityCheck (TYPE_1__*,size_t,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int* xmlStringDecodeEntities (TYPE_1__*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xmlStrlen (int*) ; 
 int /*<<< orphan*/  xmlWarningMsg (TYPE_1__*,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *) ; 

xmlChar *
xmlStringLenDecodeEntities(xmlParserCtxtPtr ctxt, const xmlChar *str, int len,
		      int what, xmlChar end, xmlChar  end2, xmlChar end3) {
    xmlChar *buffer = NULL;
    size_t buffer_size = 0;
    size_t nbchars = 0;

    xmlChar *current = NULL;
    xmlChar *rep = NULL;
    const xmlChar *last;
    xmlEntityPtr ent;
    int c,l;

    if ((ctxt == NULL) || (str == NULL) || (len < 0))
	return(NULL);
    last = str + len;

    if (((ctxt->depth > 40) &&
         ((ctxt->options & XML_PARSE_HUGE) == 0)) ||
	(ctxt->depth > 1024)) {
	xmlFatalErr(ctxt, XML_ERR_ENTITY_LOOP, NULL);
	return(NULL);
    }

    /*
     * allocate a translation buffer.
     */
    buffer_size = XML_PARSER_BIG_BUFFER_SIZE;
    buffer = (xmlChar *) xmlMallocAtomic(buffer_size);
    if (buffer == NULL) goto mem_error;

    /*
     * OK loop until we reach one of the ending char or a size limit.
     * we are operating on already parsed values.
     */
    if (str < last)
	c = CUR_SCHAR(str, l);
    else
        c = 0;
    while ((c != 0) && (c != end) && /* non input consuming loop */
	   (c != end2) && (c != end3)) {

	if (c == 0) break;
        if ((c == '&') && (str[1] == '#')) {
	    int val = xmlParseStringCharRef(ctxt, &str);
	    if (val == 0)
                goto int_error;
	    COPY_BUF(0,buffer,nbchars,val);
	    if (nbchars + XML_PARSER_BUFFER_SIZE > buffer_size) {
	        growBuffer(buffer, XML_PARSER_BUFFER_SIZE);
	    }
	} else if ((c == '&') && (what & XML_SUBSTITUTE_REF)) {
	    if (xmlParserDebugEntities)
		xmlGenericError(xmlGenericErrorContext,
			"String decoding Entity Reference: %.30s\n",
			str);
	    ent = xmlParseStringEntityRef(ctxt, &str);
	    xmlParserEntityCheck(ctxt, 0, ent, 0);
	    if (ent != NULL)
	        ctxt->nbentities += ent->checked / 2;
	    if ((ent != NULL) &&
		(ent->etype == XML_INTERNAL_PREDEFINED_ENTITY)) {
		if (ent->content != NULL) {
		    COPY_BUF(0,buffer,nbchars,ent->content[0]);
		    if (nbchars + XML_PARSER_BUFFER_SIZE > buffer_size) {
			growBuffer(buffer, XML_PARSER_BUFFER_SIZE);
		    }
		} else {
		    xmlFatalErrMsg(ctxt, XML_ERR_INTERNAL_ERROR,
			    "predefined entity has no content\n");
                    goto int_error;
		}
	    } else if ((ent != NULL) && (ent->content != NULL)) {
		ctxt->depth++;
		rep = xmlStringDecodeEntities(ctxt, ent->content, what,
			                      0, 0, 0);
		ctxt->depth--;
		if (rep == NULL)
                    goto int_error;

                current = rep;
                while (*current != 0) { /* non input consuming loop */
                    buffer[nbchars++] = *current++;
                    if (nbchars + XML_PARSER_BUFFER_SIZE > buffer_size) {
                        if (xmlParserEntityCheck(ctxt, nbchars, ent, 0))
                            goto int_error;
                        growBuffer(buffer, XML_PARSER_BUFFER_SIZE);
                    }
                }
                xmlFree(rep);
                rep = NULL;
	    } else if (ent != NULL) {
		int i = xmlStrlen(ent->name);
		const xmlChar *cur = ent->name;

		buffer[nbchars++] = '&';
		if (nbchars + i + XML_PARSER_BUFFER_SIZE > buffer_size) {
		    growBuffer(buffer, i + XML_PARSER_BUFFER_SIZE);
		}
		for (;i > 0;i--)
		    buffer[nbchars++] = *cur++;
		buffer[nbchars++] = ';';
	    }
	} else if (c == '%' && (what & XML_SUBSTITUTE_PEREF)) {
	    if (xmlParserDebugEntities)
		xmlGenericError(xmlGenericErrorContext,
			"String decoding PE Reference: %.30s\n", str);
	    ent = xmlParseStringPEReference(ctxt, &str);
	    xmlParserEntityCheck(ctxt, 0, ent, 0);
	    if (ent != NULL)
	        ctxt->nbentities += ent->checked / 2;
	    if (ent != NULL) {
                if (ent->content == NULL) {
		    /*
		     * Note: external parsed entities will not be loaded,
		     * it is not required for a non-validating parser to
		     * complete external PEreferences coming from the
		     * internal subset
		     */
		    if (((ctxt->options & XML_PARSE_NOENT) != 0) ||
			((ctxt->options & XML_PARSE_DTDVALID) != 0) ||
			(ctxt->validate != 0)) {
			xmlLoadEntityContent(ctxt, ent);
		    } else {
			xmlWarningMsg(ctxt, XML_ERR_ENTITY_PROCESSING,
		  "not validating will not read content for PE entity %s\n",
		                      ent->name, NULL);
		    }
		}
		ctxt->depth++;
		rep = xmlStringDecodeEntities(ctxt, ent->content, what,
			                      0, 0, 0);
		ctxt->depth--;
		if (rep == NULL)
                    goto int_error;
                current = rep;
                while (*current != 0) { /* non input consuming loop */
                    buffer[nbchars++] = *current++;
                    if (nbchars + XML_PARSER_BUFFER_SIZE > buffer_size) {
                        if (xmlParserEntityCheck(ctxt, nbchars, ent, 0))
                            goto int_error;
                        growBuffer(buffer, XML_PARSER_BUFFER_SIZE);
                    }
                }
                xmlFree(rep);
                rep = NULL;
	    }
	} else {
	    COPY_BUF(l,buffer,nbchars,c);
	    str += l;
	    if (nbchars + XML_PARSER_BUFFER_SIZE > buffer_size) {
	        growBuffer(buffer, XML_PARSER_BUFFER_SIZE);
	    }
	}
	if (str < last)
	    c = CUR_SCHAR(str, l);
	else
	    c = 0;
    }
    buffer[nbchars] = 0;
    return(buffer);

mem_error:
    xmlErrMemory(ctxt, NULL);
int_error:
    if (rep != NULL)
        xmlFree(rep);
    if (buffer != NULL)
        xmlFree(buffer);
    return(NULL);
}