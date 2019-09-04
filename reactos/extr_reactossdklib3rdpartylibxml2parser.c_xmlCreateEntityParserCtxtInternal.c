#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {char* directory; scalar_t__ input_id; int /*<<< orphan*/  _private; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  inputPush (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlBuildURI (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlLoadExternalEntity (char*,char*,TYPE_1__*) ; 
 TYPE_1__* xmlNewParserCtxt () ; 
 char* xmlParserGetDirectory (char*) ; 

__attribute__((used)) static xmlParserCtxtPtr
xmlCreateEntityParserCtxtInternal(const xmlChar *URL, const xmlChar *ID,
	                  const xmlChar *base, xmlParserCtxtPtr pctx) {
    xmlParserCtxtPtr ctxt;
    xmlParserInputPtr inputStream;
    char *directory = NULL;
    xmlChar *uri;

    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
	return(NULL);
    }

    if (pctx != NULL) {
        ctxt->options = pctx->options;
        ctxt->_private = pctx->_private;
	/*
	 * this is a subparser of pctx, so the input_id should be
	 * incremented to distinguish from main entity
	 */
	ctxt->input_id = pctx->input_id + 1;
    }

    uri = xmlBuildURI(URL, base);

    if (uri == NULL) {
	inputStream = xmlLoadExternalEntity((char *)URL, (char *)ID, ctxt);
	if (inputStream == NULL) {
	    xmlFreeParserCtxt(ctxt);
	    return(NULL);
	}

	inputPush(ctxt, inputStream);

	if ((ctxt->directory == NULL) && (directory == NULL))
	    directory = xmlParserGetDirectory((char *)URL);
	if ((ctxt->directory == NULL) && (directory != NULL))
	    ctxt->directory = directory;
    } else {
	inputStream = xmlLoadExternalEntity((char *)uri, (char *)ID, ctxt);
	if (inputStream == NULL) {
	    xmlFree(uri);
	    xmlFreeParserCtxt(ctxt);
	    return(NULL);
	}

	inputPush(ctxt, inputStream);

	if ((ctxt->directory == NULL) && (directory == NULL))
	    directory = xmlParserGetDirectory((char *)uri);
	if ((ctxt->directory == NULL) && (directory != NULL))
	    ctxt->directory = directory;
	xmlFree(uri);
    }
    return(ctxt);
}