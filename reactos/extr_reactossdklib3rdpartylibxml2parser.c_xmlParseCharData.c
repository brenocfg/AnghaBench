#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int xmlChar ;
struct TYPE_10__ {int* space; scalar_t__ instate; TYPE_2__* input; int /*<<< orphan*/  userData; TYPE_1__* sax; } ;
struct TYPE_9__ {int line; int col; int* cur; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* characters ) (int /*<<< orphan*/ ,int const*,int) ;int /*<<< orphan*/  (* ignorableWhitespace ) (int /*<<< orphan*/ ,int const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_BLANK_CH (int const) ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  XML_ERR_MISPLACED_CDATA_END ; 
 scalar_t__ XML_PARSER_CONTENT ; 
 scalar_t__ XML_PARSER_EOF ; 
 scalar_t__ areBlanks (TYPE_3__*,int const*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int const*,int) ; 
 scalar_t__* test_char_data ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlParseCharDataComplex (TYPE_3__*,int) ; 

void
xmlParseCharData(xmlParserCtxtPtr ctxt, int cdata) {
    const xmlChar *in;
    int nbchar = 0;
    int line = ctxt->input->line;
    int col = ctxt->input->col;
    int ccol;

    SHRINK;
    GROW;
    /*
     * Accelerated common case where input don't need to be
     * modified before passing it to the handler.
     */
    if (!cdata) {
	in = ctxt->input->cur;
	do {
get_more_space:
	    while (*in == 0x20) { in++; ctxt->input->col++; }
	    if (*in == 0xA) {
		do {
		    ctxt->input->line++; ctxt->input->col = 1;
		    in++;
		} while (*in == 0xA);
		goto get_more_space;
	    }
	    if (*in == '<') {
		nbchar = in - ctxt->input->cur;
		if (nbchar > 0) {
		    const xmlChar *tmp = ctxt->input->cur;
		    ctxt->input->cur = in;

		    if ((ctxt->sax != NULL) &&
		        (ctxt->sax->ignorableWhitespace !=
		         ctxt->sax->characters)) {
			if (areBlanks(ctxt, tmp, nbchar, 1)) {
			    if (ctxt->sax->ignorableWhitespace != NULL)
				ctxt->sax->ignorableWhitespace(ctxt->userData,
						       tmp, nbchar);
			} else {
			    if (ctxt->sax->characters != NULL)
				ctxt->sax->characters(ctxt->userData,
						      tmp, nbchar);
			    if (*ctxt->space == -1)
			        *ctxt->space = -2;
			}
		    } else if ((ctxt->sax != NULL) &&
		               (ctxt->sax->characters != NULL)) {
			ctxt->sax->characters(ctxt->userData,
					      tmp, nbchar);
		    }
		}
		return;
	    }

get_more:
            ccol = ctxt->input->col;
	    while (test_char_data[*in]) {
		in++;
		ccol++;
	    }
	    ctxt->input->col = ccol;
	    if (*in == 0xA) {
		do {
		    ctxt->input->line++; ctxt->input->col = 1;
		    in++;
		} while (*in == 0xA);
		goto get_more;
	    }
	    if (*in == ']') {
		if ((in[1] == ']') && (in[2] == '>')) {
		    xmlFatalErr(ctxt, XML_ERR_MISPLACED_CDATA_END, NULL);
		    ctxt->input->cur = in + 1;
		    return;
		}
		in++;
		ctxt->input->col++;
		goto get_more;
	    }
	    nbchar = in - ctxt->input->cur;
	    if (nbchar > 0) {
		if ((ctxt->sax != NULL) &&
		    (ctxt->sax->ignorableWhitespace !=
		     ctxt->sax->characters) &&
		    (IS_BLANK_CH(*ctxt->input->cur))) {
		    const xmlChar *tmp = ctxt->input->cur;
		    ctxt->input->cur = in;

		    if (areBlanks(ctxt, tmp, nbchar, 0)) {
		        if (ctxt->sax->ignorableWhitespace != NULL)
			    ctxt->sax->ignorableWhitespace(ctxt->userData,
							   tmp, nbchar);
		    } else {
		        if (ctxt->sax->characters != NULL)
			    ctxt->sax->characters(ctxt->userData,
						  tmp, nbchar);
			if (*ctxt->space == -1)
			    *ctxt->space = -2;
		    }
                    line = ctxt->input->line;
                    col = ctxt->input->col;
		} else if (ctxt->sax != NULL) {
		    if (ctxt->sax->characters != NULL)
			ctxt->sax->characters(ctxt->userData,
					      ctxt->input->cur, nbchar);
                    line = ctxt->input->line;
                    col = ctxt->input->col;
		}
                /* something really bad happened in the SAX callback */
                if (ctxt->instate != XML_PARSER_CONTENT)
                    return;
	    }
	    ctxt->input->cur = in;
	    if (*in == 0xD) {
		in++;
		if (*in == 0xA) {
		    ctxt->input->cur = in;
		    in++;
		    ctxt->input->line++; ctxt->input->col = 1;
		    continue; /* while */
		}
		in--;
	    }
	    if (*in == '<') {
		return;
	    }
	    if (*in == '&') {
		return;
	    }
	    SHRINK;
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF)
		return;
	    in = ctxt->input->cur;
	} while (((*in >= 0x20) && (*in <= 0x7F)) || (*in == 0x09));
	nbchar = 0;
    }
    ctxt->input->line = line;
    ctxt->input->col = col;
    xmlParseCharDataComplex(ctxt, cdata);
}