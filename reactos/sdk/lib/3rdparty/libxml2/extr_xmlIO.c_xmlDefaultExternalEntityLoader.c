#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_7__ {int options; } ;

/* Variables and functions */
 int XML_PARSE_NONET ; 
 int /*<<< orphan*/  __xmlLoaderErr (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/ * xmlNewInputFromFile (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * xmlNoNetExternalEntityLoader (char const*,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlResolveResourceFromCatalog (char const*,char const*,TYPE_1__*) ; 

__attribute__((used)) static xmlParserInputPtr
xmlDefaultExternalEntityLoader(const char *URL, const char *ID,
                               xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr ret = NULL;
    xmlChar *resource = NULL;

#ifdef DEBUG_EXTERNAL_ENTITIES
    xmlGenericError(xmlGenericErrorContext,
                    "xmlDefaultExternalEntityLoader(%s, xxx)\n", URL);
#endif
    if ((ctxt != NULL) && (ctxt->options & XML_PARSE_NONET)) {
        int options = ctxt->options;

	ctxt->options -= XML_PARSE_NONET;
        ret = xmlNoNetExternalEntityLoader(URL, ID, ctxt);
	ctxt->options = options;
	return(ret);
    }
#ifdef LIBXML_CATALOG_ENABLED
    resource = xmlResolveResourceFromCatalog(URL, ID, ctxt);
#endif

    if (resource == NULL)
        resource = (xmlChar *) URL;

    if (resource == NULL) {
        if (ID == NULL)
            ID = "NULL";
        __xmlLoaderErr(ctxt, "failed to load external entity \"%s\"\n", ID);
        return (NULL);
    }
    ret = xmlNewInputFromFile(ctxt, (const char *) resource);
    if ((resource != NULL) && (resource != (xmlChar *) URL))
        xmlFree(resource);
    return (ret);
}