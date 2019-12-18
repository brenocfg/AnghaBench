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
typedef  TYPE_1__* xmlParserInputPtr ;
typedef  TYPE_2__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
struct TYPE_9__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {TYPE_2__* buf; int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CHAR_ENCODING_NONE ; 
 int /*<<< orphan*/  inputPush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xmlBufResetInput (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeParserInputBuffer (TYPE_2__*) ; 
 TYPE_1__* xmlNewInputStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNewParserCtxt () ; 
 TYPE_2__* xmlParserInputBufferCreateMem (char const*,int,int /*<<< orphan*/ ) ; 

xmlParserCtxtPtr
xmlCreateMemoryParserCtxt(const char *buffer, int size) {
    xmlParserCtxtPtr ctxt;
    xmlParserInputPtr input;
    xmlParserInputBufferPtr buf;

    if (buffer == NULL)
	return(NULL);
    if (size <= 0)
	return(NULL);

    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL)
	return(NULL);

    /* TODO: xmlParserInputBufferCreateStatic, requires some serious changes */
    buf = xmlParserInputBufferCreateMem(buffer, size, XML_CHAR_ENCODING_NONE);
    if (buf == NULL) {
	xmlFreeParserCtxt(ctxt);
	return(NULL);
    }

    input = xmlNewInputStream(ctxt);
    if (input == NULL) {
	xmlFreeParserInputBuffer(buf);
	xmlFreeParserCtxt(ctxt);
	return(NULL);
    }

    input->filename = NULL;
    input->buf = buf;
    xmlBufResetInput(input->buf->buffer, input);

    inputPush(ctxt, input);
    return(ctxt);
}