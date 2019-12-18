#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlSAXHandlerV1 ;
typedef  TYPE_1__* xmlSAXHandlerPtr ;
typedef  int /*<<< orphan*/  xmlSAXHandler ;
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  int /*<<< orphan*/ * xmlParserInputBufferPtr ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlInputReadCallback ;
typedef  int /*<<< orphan*/  (* xmlInputCloseCallback ) (void*) ;
typedef  int /*<<< orphan*/  xmlCharEncoding ;
struct TYPE_15__ {void* userData; TYPE_1__* sax; } ;
struct TYPE_14__ {scalar_t__ initialized; } ;

/* Variables and functions */
 scalar_t__ XML_SAX2_MAGIC ; 
 int /*<<< orphan*/  inputPush (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlDefaultSAXHandler ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlFreeParserInputBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/ * xmlNewIOInputStream (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlNewParserCtxt () ; 
 int /*<<< orphan*/ * xmlParserInputBufferCreateIO (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (void*),void*,int /*<<< orphan*/ ) ; 

xmlParserCtxtPtr
xmlCreateIOParserCtxt(xmlSAXHandlerPtr sax, void *user_data,
	xmlInputReadCallback   ioread, xmlInputCloseCallback  ioclose,
	void *ioctx, xmlCharEncoding enc) {
    xmlParserCtxtPtr ctxt;
    xmlParserInputPtr inputStream;
    xmlParserInputBufferPtr buf;

    if (ioread == NULL) return(NULL);

    buf = xmlParserInputBufferCreateIO(ioread, ioclose, ioctx, enc);
    if (buf == NULL) {
        if (ioclose != NULL)
            ioclose(ioctx);
        return (NULL);
    }

    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
	xmlFreeParserInputBuffer(buf);
	return(NULL);
    }
    if (sax != NULL) {
#ifdef LIBXML_SAX1_ENABLED
	if (ctxt->sax != (xmlSAXHandlerPtr) &xmlDefaultSAXHandler)
#endif /* LIBXML_SAX1_ENABLED */
	    xmlFree(ctxt->sax);
	ctxt->sax = (xmlSAXHandlerPtr) xmlMalloc(sizeof(xmlSAXHandler));
	if (ctxt->sax == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    xmlFreeParserCtxt(ctxt);
	    return(NULL);
	}
	memset(ctxt->sax, 0, sizeof(xmlSAXHandler));
	if (sax->initialized == XML_SAX2_MAGIC)
	    memcpy(ctxt->sax, sax, sizeof(xmlSAXHandler));
	else
	    memcpy(ctxt->sax, sax, sizeof(xmlSAXHandlerV1));
	if (user_data != NULL)
	    ctxt->userData = user_data;
    }

    inputStream = xmlNewIOInputStream(ctxt, buf, enc);
    if (inputStream == NULL) {
	xmlFreeParserCtxt(ctxt);
	return(NULL);
    }
    inputPush(ctxt, inputStream);

    return(ctxt);
}