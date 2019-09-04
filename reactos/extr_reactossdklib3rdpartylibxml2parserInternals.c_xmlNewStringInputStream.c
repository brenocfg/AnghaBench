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
typedef  TYPE_1__* xmlParserInputPtr ;
typedef  int /*<<< orphan*/  xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/  const* end; int /*<<< orphan*/  const* cur; int /*<<< orphan*/  const* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlErrInternal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlErrMemory (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 TYPE_1__* xmlNewInputStream (int /*<<< orphan*/ ) ; 
 scalar_t__ xmlParserDebugEntities ; 
 size_t xmlStrlen (int /*<<< orphan*/  const*) ; 

xmlParserInputPtr
xmlNewStringInputStream(xmlParserCtxtPtr ctxt, const xmlChar *buffer) {
    xmlParserInputPtr input;

    if (buffer == NULL) {
        xmlErrInternal(ctxt, "xmlNewStringInputStream string = NULL\n",
	               NULL);
	return(NULL);
    }
    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"new fixed input: %.30s\n", buffer);
    input = xmlNewInputStream(ctxt);
    if (input == NULL) {
        xmlErrMemory(ctxt,  "couldn't allocate a new input stream\n");
	return(NULL);
    }
    input->base = buffer;
    input->cur = buffer;
    input->length = xmlStrlen(buffer);
    input->end = &buffer[input->length];
    return(input);
}