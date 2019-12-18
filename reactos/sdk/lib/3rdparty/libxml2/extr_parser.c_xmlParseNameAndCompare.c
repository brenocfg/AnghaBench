#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_6__ {scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_5__ {scalar_t__* cur; int /*<<< orphan*/  col; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_BLANK_CH (scalar_t__ const) ; 
 scalar_t__ XML_PARSER_EOF ; 
 scalar_t__* xmlParseName (TYPE_2__*) ; 

__attribute__((used)) static const xmlChar *
xmlParseNameAndCompare(xmlParserCtxtPtr ctxt, xmlChar const *other) {
    register const xmlChar *cmp = other;
    register const xmlChar *in;
    const xmlChar *ret;

    GROW;
    if (ctxt->instate == XML_PARSER_EOF)
        return(NULL);

    in = ctxt->input->cur;
    while (*in != 0 && *in == *cmp) {
	++in;
	++cmp;
	ctxt->input->col++;
    }
    if (*cmp == 0 && (*in == '>' || IS_BLANK_CH (*in))) {
	/* success */
	ctxt->input->cur = in;
	return (const xmlChar*) 1;
    }
    /* failure (or end of input buffer), check with full function */
    ret = xmlParseName (ctxt);
    /* strings coming from the dictionary direct compare possible */
    if (ret == other) {
	return (const xmlChar*) 1;
    }
    return ret;
}