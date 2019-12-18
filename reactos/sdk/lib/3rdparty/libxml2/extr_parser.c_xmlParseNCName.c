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
typedef  int xmlChar ;
struct TYPE_8__ {int options; int nbChars; TYPE_1__* input; int /*<<< orphan*/  dict; } ;
struct TYPE_7__ {int* cur; int* end; int col; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ERR_NAME_TOO_LONG ; 
 int XML_MAX_NAME_LENGTH ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  nbParseNCName ; 
 int* xmlDictLookup (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int const* xmlParseNCNameComplex (TYPE_2__*) ; 

__attribute__((used)) static const xmlChar *
xmlParseNCName(xmlParserCtxtPtr ctxt) {
    const xmlChar *in, *e;
    const xmlChar *ret;
    int count = 0;

#ifdef DEBUG
    nbParseNCName++;
#endif

    /*
     * Accelerator for simple ASCII names
     */
    in = ctxt->input->cur;
    e = ctxt->input->end;
    if ((((*in >= 0x61) && (*in <= 0x7A)) ||
	 ((*in >= 0x41) && (*in <= 0x5A)) ||
	 (*in == '_')) && (in < e)) {
	in++;
	while ((((*in >= 0x61) && (*in <= 0x7A)) ||
	        ((*in >= 0x41) && (*in <= 0x5A)) ||
	        ((*in >= 0x30) && (*in <= 0x39)) ||
	        (*in == '_') || (*in == '-') ||
	        (*in == '.')) && (in < e))
	    in++;
	if (in >= e)
	    goto complex;
	if ((*in > 0) && (*in < 0x80)) {
	    count = in - ctxt->input->cur;
            if ((count > XML_MAX_NAME_LENGTH) &&
                ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NCName");
                return(NULL);
            }
	    ret = xmlDictLookup(ctxt->dict, ctxt->input->cur, count);
	    ctxt->input->cur = in;
	    ctxt->nbChars += count;
	    ctxt->input->col += count;
	    if (ret == NULL) {
	        xmlErrMemory(ctxt, NULL);
	    }
	    return(ret);
	}
    }
complex:
    return(xmlParseNCNameComplex(ctxt));
}