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
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {int options; scalar_t__ instate; int /*<<< orphan*/  dict; TYPE_1__* input; } ;
struct TYPE_7__ {int cur; } ;

/* Variables and functions */
 size_t BASE_PTR ; 
 int CUR_CHAR (int) ; 
 size_t CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 int /*<<< orphan*/  XML_ERR_NAME_TOO_LONG ; 
 int XML_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  XML_PARSER_CHUNK_SIZE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  nbParseNCNameComplex ; 
 int /*<<< orphan*/  const* xmlDictLookup (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xmlIsNameChar (TYPE_2__*,int) ; 
 int /*<<< orphan*/  xmlIsNameStartChar (TYPE_2__*,int) ; 

__attribute__((used)) static const xmlChar *
xmlParseNCNameComplex(xmlParserCtxtPtr ctxt) {
    int len = 0, l;
    int c;
    int count = 0;
    size_t startPosition = 0;

#ifdef DEBUG
    nbParseNCNameComplex++;
#endif

    /*
     * Handler for more complex cases
     */
    GROW;
    startPosition = CUR_PTR - BASE_PTR;
    c = CUR_CHAR(l);
    if ((c == ' ') || (c == '>') || (c == '/') || /* accelerators */
	(!xmlIsNameStartChar(ctxt, c) || (c == ':'))) {
	return(NULL);
    }

    while ((c != ' ') && (c != '>') && (c != '/') && /* test bigname.xml */
	   (xmlIsNameChar(ctxt, c) && (c != ':'))) {
	if (count++ > XML_PARSER_CHUNK_SIZE) {
            if ((len > XML_MAX_NAME_LENGTH) &&
                ((ctxt->options & XML_PARSE_HUGE) == 0)) {
                xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NCName");
                return(NULL);
            }
	    count = 0;
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF)
                return(NULL);
	}
	len += l;
	NEXTL(l);
	c = CUR_CHAR(l);
	if (c == 0) {
	    count = 0;
	    /*
	     * when shrinking to extend the buffer we really need to preserve
	     * the part of the name we already parsed. Hence rolling back
	     * by current lenght.
	     */
	    ctxt->input->cur -= l;
	    GROW;
            if (ctxt->instate == XML_PARSER_EOF)
                return(NULL);
	    ctxt->input->cur += l;
	    c = CUR_CHAR(l);
	}
    }
    if ((len > XML_MAX_NAME_LENGTH) &&
        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
        xmlFatalErr(ctxt, XML_ERR_NAME_TOO_LONG, "NCName");
        return(NULL);
    }
    return(xmlDictLookup(ctxt->dict, (BASE_PTR + startPosition), len));
}