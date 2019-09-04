#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  char xmlChar ;
struct TYPE_7__ {TYPE_1__* input; } ;
struct TYPE_6__ {char* cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROW ; 
 scalar_t__ IS_BLANK_CH (char const) ; 
 char const* xmlParseNameAndCompare (TYPE_2__*,char const*) ; 
 char* xmlParseQName (TYPE_2__*,char const**) ; 

__attribute__((used)) static const xmlChar *
xmlParseQNameAndCompare(xmlParserCtxtPtr ctxt, xmlChar const *name,
                        xmlChar const *prefix) {
    const xmlChar *cmp;
    const xmlChar *in;
    const xmlChar *ret;
    const xmlChar *prefix2;

    if (prefix == NULL) return(xmlParseNameAndCompare(ctxt, name));

    GROW;
    in = ctxt->input->cur;

    cmp = prefix;
    while (*in != 0 && *in == *cmp) {
	++in;
	++cmp;
    }
    if ((*cmp == 0) && (*in == ':')) {
        in++;
	cmp = name;
	while (*in != 0 && *in == *cmp) {
	    ++in;
	    ++cmp;
	}
	if (*cmp == 0 && (*in == '>' || IS_BLANK_CH (*in))) {
	    /* success */
	    ctxt->input->cur = in;
	    return((const xmlChar*) 1);
	}
    }
    /*
     * all strings coms from the dictionary, equality can be done directly
     */
    ret = xmlParseQName (ctxt, &prefix2);
    if ((ret == name) && (prefix == prefix2))
	return((const xmlChar*) 1);
    return ret;
}