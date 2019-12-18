#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int (* readcallback ) (int /*<<< orphan*/ ,char*,int) ;int compressed; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * raw; int /*<<< orphan*/  rawconsumed; void* error; int /*<<< orphan*/ * encoder; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int MINLEN ; 
 void* XML_ERR_NO_MEMORY ; 
 void* XML_IO_BUFFER_FULL ; 
 void* XML_IO_ENCODER ; 
 void* XML_IO_NO_INPUT ; 
 int __libxml2_xzcompressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endOfInput ; 
 int stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int xmlBufAdd (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xmlBufAddLen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ xmlBufAvail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlBufCreate () ; 
 scalar_t__ xmlBufEnd (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlBufGrow (int /*<<< orphan*/ *,int) ; 
 unsigned int xmlBufUse (int /*<<< orphan*/ *) ; 
 int xmlCharEncInput (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int /*<<< orphan*/  xmlIOErr (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlIOErrMemory (char*) ; 
 int xmlXzfileRead (int /*<<< orphan*/ ,char*,int) ; 

int
xmlParserInputBufferGrow(xmlParserInputBufferPtr in, int len) {
    char *buffer = NULL;
    int res = 0;
    int nbchars = 0;

    if ((in == NULL) || (in->error)) return(-1);
    if ((len <= MINLEN) && (len != 4))
        len = MINLEN;

    if (xmlBufAvail(in->buffer) <= 0) {
	xmlIOErr(XML_IO_BUFFER_FULL, NULL);
	in->error = XML_IO_BUFFER_FULL;
	return(-1);
    }

    if (xmlBufGrow(in->buffer, len + 1) < 0) {
        xmlIOErrMemory("growing input buffer");
        in->error = XML_ERR_NO_MEMORY;
        return(-1);
    }
    buffer = (char *)xmlBufEnd(in->buffer);

    /*
     * Call the read method for this I/O type.
     */
    if (in->readcallback != NULL) {
	res = in->readcallback(in->context, &buffer[0], len);
	if (res <= 0)
	    in->readcallback = endOfInput;
    } else {
	xmlIOErr(XML_IO_NO_INPUT, NULL);
	in->error = XML_IO_NO_INPUT;
	return(-1);
    }
    if (res < 0) {
	return(-1);
    }

    /*
     * try to establish compressed status of input if not done already
     */
    if (in->compressed == -1) {
#ifdef LIBXML_LZMA_ENABLED
	if (in->readcallback == xmlXzfileRead)
            in->compressed = __libxml2_xzcompressed(in->context);
#endif
    }

    len = res;
    if (in->encoder != NULL) {
        unsigned int use;

        /*
	 * Store the data in the incoming raw buffer
	 */
        if (in->raw == NULL) {
	    in->raw = xmlBufCreate();
	}
	res = xmlBufAdd(in->raw, (const xmlChar *) buffer, len);
	if (res != 0)
	    return(-1);

	/*
	 * convert as much as possible to the parser reading buffer.
	 */
	use = xmlBufUse(in->raw);
	nbchars = xmlCharEncInput(in, 1);
	if (nbchars < 0) {
	    xmlIOErr(XML_IO_ENCODER, NULL);
	    in->error = XML_IO_ENCODER;
	    return(-1);
	}
	in->rawconsumed += (use - xmlBufUse(in->raw));
    } else {
	nbchars = len;
        xmlBufAddLen(in->buffer, nbchars);
    }
#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext,
	    "I/O: read %d chars, buffer %d\n",
            nbchars, xmlBufUse(in->buffer));
#endif
    return(nbchars);
}