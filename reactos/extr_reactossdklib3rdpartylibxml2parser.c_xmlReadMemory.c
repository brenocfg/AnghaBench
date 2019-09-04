#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlCreateMemoryParserCtxt (char const*,int) ; 
 int /*<<< orphan*/ * xmlDoRead (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlInitParser () ; 

xmlDocPtr
xmlReadMemory(const char *buffer, int size, const char *URL, const char *encoding, int options)
{
    xmlParserCtxtPtr ctxt;

    xmlInitParser();
    ctxt = xmlCreateMemoryParserCtxt(buffer, size);
    if (ctxt == NULL)
        return (NULL);
    return (xmlDoRead(ctxt, URL, encoding, options, 0));
}