#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputPtr ;
typedef  TYPE_2__* xmlParserInputBufferPtr ;
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_16__ {char* directory; } ;
struct TYPE_15__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_14__ {char* filename; char* directory; TYPE_2__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CHAR_ENCODING_NONE ; 
 int /*<<< orphan*/  __xmlLoaderErr (TYPE_3__*,char*,char const*) ; 
 int /*<<< orphan*/  xmlBufResetInput (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ xmlCanonicPath (int /*<<< orphan*/  const*) ; 
 TYPE_1__* xmlCheckHTTPInput (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_1__* xmlNewInputStream (TYPE_3__*) ; 
 scalar_t__ xmlParserDebugEntities ; 
 char* xmlParserGetDirectory (char const*) ; 
 TYPE_2__* xmlParserInputBufferCreateFilename (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* xmlStrdup (int /*<<< orphan*/  const*) ; 

xmlParserInputPtr
xmlNewInputFromFile(xmlParserCtxtPtr ctxt, const char *filename) {
    xmlParserInputBufferPtr buf;
    xmlParserInputPtr inputStream;
    char *directory = NULL;
    xmlChar *URI = NULL;

    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"new input from file: %s\n", filename);
    if (ctxt == NULL) return(NULL);
    buf = xmlParserInputBufferCreateFilename(filename, XML_CHAR_ENCODING_NONE);
    if (buf == NULL) {
	if (filename == NULL)
	    __xmlLoaderErr(ctxt,
	                   "failed to load external entity: NULL filename \n",
			   NULL);
	else
	    __xmlLoaderErr(ctxt, "failed to load external entity \"%s\"\n",
			   (const char *) filename);
	return(NULL);
    }

    inputStream = xmlNewInputStream(ctxt);
    if (inputStream == NULL)
	return(NULL);

    inputStream->buf = buf;
    inputStream = xmlCheckHTTPInput(ctxt, inputStream);
    if (inputStream == NULL)
        return(NULL);

    if (inputStream->filename == NULL)
	URI = xmlStrdup((xmlChar *) filename);
    else
	URI = xmlStrdup((xmlChar *) inputStream->filename);
    directory = xmlParserGetDirectory((const char *) URI);
    if (inputStream->filename != NULL) xmlFree((char *)inputStream->filename);
    inputStream->filename = (char *) xmlCanonicPath((const xmlChar *) URI);
    if (URI != NULL) xmlFree((char *) URI);
    inputStream->directory = directory;

    xmlBufResetInput(inputStream->buf->buffer, inputStream);
    if ((ctxt->directory == NULL) && (directory != NULL))
        ctxt->directory = (char *) xmlStrdup((const xmlChar *) directory);
    return(inputStream);
}