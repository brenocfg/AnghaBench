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
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
struct TYPE_5__ {int /*<<< orphan*/ * closecallback; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_CHAR_ENCODING_NONE ; 
 int /*<<< orphan*/  inputPush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlDoRead (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeParserInputBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlInitParser () ; 
 int /*<<< orphan*/ * xmlNewIOInputStream (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlNewParserCtxt () ; 
 TYPE_1__* xmlParserInputBufferCreateFd (int,int /*<<< orphan*/ ) ; 

xmlDocPtr
xmlReadFd(int fd, const char *URL, const char *encoding, int options)
{
    xmlParserCtxtPtr ctxt;
    xmlParserInputBufferPtr input;
    xmlParserInputPtr stream;

    if (fd < 0)
        return (NULL);
    xmlInitParser();

    input = xmlParserInputBufferCreateFd(fd, XML_CHAR_ENCODING_NONE);
    if (input == NULL)
        return (NULL);
    input->closecallback = NULL;
    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
        xmlFreeParserInputBuffer(input);
        return (NULL);
    }
    stream = xmlNewIOInputStream(ctxt, input, XML_CHAR_ENCODING_NONE);
    if (stream == NULL) {
        xmlFreeParserInputBuffer(input);
	xmlFreeParserCtxt(ctxt);
        return (NULL);
    }
    inputPush(ctxt, stream);
    return (xmlDoRead(ctxt, URL, encoding, options, 0));
}