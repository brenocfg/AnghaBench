#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  char xmlChar ;
struct TYPE_8__ {scalar_t__ instate; int options; TYPE_1__* input; } ;
struct TYPE_7__ {int line; int col; char* end; char* base; } ;

/* Variables and functions */
 char const* CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  XML_ERR_ATTRIBUTE_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_ATTRIBUTE_NOT_STARTED ; 
 int XML_MAX_TEXT_LENGTH ; 
 scalar_t__ XML_PARSER_ATTRIBUTE_VALUE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 char* xmlParseAttValueComplex (TYPE_2__*,int*,int) ; 
 char* xmlStrndup (char const*,int) ; 

__attribute__((used)) static xmlChar *
xmlParseAttValueInternal(xmlParserCtxtPtr ctxt, int *len, int *alloc,
                         int normalize)
{
    xmlChar limit = 0;
    const xmlChar *in = NULL, *start, *end, *last;
    xmlChar *ret = NULL;
    int line, col;

    GROW;
    in = (xmlChar *) CUR_PTR;
    line = ctxt->input->line;
    col = ctxt->input->col;
    if (*in != '"' && *in != '\'') {
        xmlFatalErr(ctxt, XML_ERR_ATTRIBUTE_NOT_STARTED, NULL);
        return (NULL);
    }
    ctxt->instate = XML_PARSER_ATTRIBUTE_VALUE;

    /*
     * try to handle in this routine the most common case where no
     * allocation of a new string is required and where content is
     * pure ASCII.
     */
    limit = *in++;
    col++;
    end = ctxt->input->end;
    start = in;
    if (in >= end) {
        const xmlChar *oldbase = ctxt->input->base;
	GROW;
	if (oldbase != ctxt->input->base) {
	    long delta = ctxt->input->base - oldbase;
	    start = start + delta;
	    in = in + delta;
	}
	end = ctxt->input->end;
    }
    if (normalize) {
        /*
	 * Skip any leading spaces
	 */
	while ((in < end) && (*in != limit) &&
	       ((*in == 0x20) || (*in == 0x9) ||
	        (*in == 0xA) || (*in == 0xD))) {
	    if (*in == 0xA) {
	        line++; col = 1;
	    } else {
	        col++;
	    }
	    in++;
	    start = in;
	    if (in >= end) {
		const xmlChar *oldbase = ctxt->input->base;
		GROW;
                if (ctxt->instate == XML_PARSER_EOF)
                    return(NULL);
		if (oldbase != ctxt->input->base) {
		    long delta = ctxt->input->base - oldbase;
		    start = start + delta;
		    in = in + delta;
		}
		end = ctxt->input->end;
                if (((in - start) > XML_MAX_TEXT_LENGTH) &&
                    ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                    xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                                   "AttValue length too long\n");
                    return(NULL);
                }
	    }
	}
	while ((in < end) && (*in != limit) && (*in >= 0x20) &&
	       (*in <= 0x7f) && (*in != '&') && (*in != '<')) {
	    col++;
	    if ((*in++ == 0x20) && (*in == 0x20)) break;
	    if (in >= end) {
		const xmlChar *oldbase = ctxt->input->base;
		GROW;
                if (ctxt->instate == XML_PARSER_EOF)
                    return(NULL);
		if (oldbase != ctxt->input->base) {
		    long delta = ctxt->input->base - oldbase;
		    start = start + delta;
		    in = in + delta;
		}
		end = ctxt->input->end;
                if (((in - start) > XML_MAX_TEXT_LENGTH) &&
                    ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                    xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                                   "AttValue length too long\n");
                    return(NULL);
                }
	    }
	}
	last = in;
	/*
	 * skip the trailing blanks
	 */
	while ((last[-1] == 0x20) && (last > start)) last--;
	while ((in < end) && (*in != limit) &&
	       ((*in == 0x20) || (*in == 0x9) ||
	        (*in == 0xA) || (*in == 0xD))) {
	    if (*in == 0xA) {
	        line++, col = 1;
	    } else {
	        col++;
	    }
	    in++;
	    if (in >= end) {
		const xmlChar *oldbase = ctxt->input->base;
		GROW;
                if (ctxt->instate == XML_PARSER_EOF)
                    return(NULL);
		if (oldbase != ctxt->input->base) {
		    long delta = ctxt->input->base - oldbase;
		    start = start + delta;
		    in = in + delta;
		    last = last + delta;
		}
		end = ctxt->input->end;
                if (((in - start) > XML_MAX_TEXT_LENGTH) &&
                    ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                    xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                                   "AttValue length too long\n");
                    return(NULL);
                }
	    }
	}
        if (((in - start) > XML_MAX_TEXT_LENGTH) &&
            ((ctxt->options & XML_PARSE_HUGE) == 0)) {
            xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                           "AttValue length too long\n");
            return(NULL);
        }
	if (*in != limit) goto need_complex;
    } else {
	while ((in < end) && (*in != limit) && (*in >= 0x20) &&
	       (*in <= 0x7f) && (*in != '&') && (*in != '<')) {
	    in++;
	    col++;
	    if (in >= end) {
		const xmlChar *oldbase = ctxt->input->base;
		GROW;
                if (ctxt->instate == XML_PARSER_EOF)
                    return(NULL);
		if (oldbase != ctxt->input->base) {
		    long delta = ctxt->input->base - oldbase;
		    start = start + delta;
		    in = in + delta;
		}
		end = ctxt->input->end;
                if (((in - start) > XML_MAX_TEXT_LENGTH) &&
                    ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                    xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                                   "AttValue length too long\n");
                    return(NULL);
                }
	    }
	}
	last = in;
        if (((in - start) > XML_MAX_TEXT_LENGTH) &&
            ((ctxt->options & XML_PARSE_HUGE) == 0)) {
            xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                           "AttValue length too long\n");
            return(NULL);
        }
	if (*in != limit) goto need_complex;
    }
    in++;
    col++;
    if (len != NULL) {
        *len = last - start;
        ret = (xmlChar *) start;
    } else {
        if (alloc) *alloc = 1;
        ret = xmlStrndup(start, last - start);
    }
    CUR_PTR = in;
    ctxt->input->line = line;
    ctxt->input->col = col;
    if (alloc) *alloc = 0;
    return ret;
need_complex:
    if (alloc) *alloc = 1;
    return xmlParseAttValueComplex(ctxt, len, normalize);
}