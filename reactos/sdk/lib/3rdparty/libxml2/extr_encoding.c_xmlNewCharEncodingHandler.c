#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlCharEncodingOutputFunc ;
typedef  int /*<<< orphan*/  xmlCharEncodingInputFunc ;
typedef  TYPE_1__* xmlCharEncodingHandlerPtr ;
typedef  int /*<<< orphan*/  xmlCharEncodingHandler ;
struct TYPE_5__ {char* name; int /*<<< orphan*/ * uconv_out; int /*<<< orphan*/ * uconv_in; int /*<<< orphan*/ * iconv_out; int /*<<< orphan*/ * iconv_in; int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_I18N_NO_NAME ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char toupper (char const) ; 
 int /*<<< orphan*/  xmlEncodingErr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlEncodingErrMemory (char*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 char* xmlGetEncodingAlias (char const*) ; 
 scalar_t__ xmlMalloc (int) ; 
 char* xmlMemStrdup (char*) ; 
 int /*<<< orphan*/  xmlRegisterCharEncodingHandler (TYPE_1__*) ; 

xmlCharEncodingHandlerPtr
xmlNewCharEncodingHandler(const char *name,
                          xmlCharEncodingInputFunc input,
                          xmlCharEncodingOutputFunc output) {
    xmlCharEncodingHandlerPtr handler;
    const char *alias;
    char upper[500];
    int i;
    char *up = NULL;

    /*
     * Do the alias resolution
     */
    alias = xmlGetEncodingAlias(name);
    if (alias != NULL)
	name = alias;

    /*
     * Keep only the uppercase version of the encoding.
     */
    if (name == NULL) {
        xmlEncodingErr(XML_I18N_NO_NAME,
		       "xmlNewCharEncodingHandler : no name !\n", NULL);
	return(NULL);
    }
    for (i = 0;i < 499;i++) {
        upper[i] = toupper(name[i]);
	if (upper[i] == 0) break;
    }
    upper[i] = 0;
    up = xmlMemStrdup(upper);
    if (up == NULL) {
        xmlEncodingErrMemory("xmlNewCharEncodingHandler : out of memory !\n");
	return(NULL);
    }

    /*
     * allocate and fill-up an handler block.
     */
    handler = (xmlCharEncodingHandlerPtr)
              xmlMalloc(sizeof(xmlCharEncodingHandler));
    if (handler == NULL) {
        xmlFree(up);
        xmlEncodingErrMemory("xmlNewCharEncodingHandler : out of memory !\n");
	return(NULL);
    }
    memset(handler, 0, sizeof(xmlCharEncodingHandler));
    handler->input = input;
    handler->output = output;
    handler->name = up;

#ifdef LIBXML_ICONV_ENABLED
    handler->iconv_in = NULL;
    handler->iconv_out = NULL;
#endif
#ifdef LIBXML_ICU_ENABLED
    handler->uconv_in = NULL;
    handler->uconv_out = NULL;
#endif

    /*
     * registers and returns the handler.
     */
    xmlRegisterCharEncodingHandler(handler);
#ifdef DEBUG_ENCODING
    xmlGenericError(xmlGenericErrorContext,
	    "Registered encoding handler for %s\n", name);
#endif
    return(handler);
}