#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/ * xmlCharEncodingHandlerPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {int /*<<< orphan*/ * myDoc; scalar_t__ recovery; scalar_t__ wellFormed; TYPE_1__* input; } ;
struct TYPE_8__ {char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlCtxtUseOptionsInternal (TYPE_2__*,int,char const*) ; 
 int /*<<< orphan*/ * xmlFindCharEncodingHandler (char const*) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParseDocument (TYPE_2__*) ; 
 scalar_t__ xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlSwitchToEncoding (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlDocPtr
xmlDoRead(xmlParserCtxtPtr ctxt, const char *URL, const char *encoding,
          int options, int reuse)
{
    xmlDocPtr ret;

    xmlCtxtUseOptionsInternal(ctxt, options, encoding);
    if (encoding != NULL) {
        xmlCharEncodingHandlerPtr hdlr;

	hdlr = xmlFindCharEncodingHandler(encoding);
	if (hdlr != NULL)
	    xmlSwitchToEncoding(ctxt, hdlr);
    }
    if ((URL != NULL) && (ctxt->input != NULL) &&
        (ctxt->input->filename == NULL))
        ctxt->input->filename = (char *) xmlStrdup((const xmlChar *) URL);
    xmlParseDocument(ctxt);
    if ((ctxt->wellFormed) || ctxt->recovery)
        ret = ctxt->myDoc;
    else {
        ret = NULL;
	if (ctxt->myDoc != NULL) {
	    xmlFreeDoc(ctxt->myDoc);
	}
    }
    ctxt->myDoc = NULL;
    if (!reuse) {
	xmlFreeParserCtxt(ctxt);
    }

    return (ret);
}