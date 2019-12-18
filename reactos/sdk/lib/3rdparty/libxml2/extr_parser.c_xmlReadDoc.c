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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlCreateDocParserCtxt (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlDoRead (int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlInitParser () ; 

xmlDocPtr
xmlReadDoc(const xmlChar * cur, const char *URL, const char *encoding, int options)
{
    xmlParserCtxtPtr ctxt;

    if (cur == NULL)
        return (NULL);
    xmlInitParser();

    ctxt = xmlCreateDocParserCtxt(cur);
    if (ctxt == NULL)
        return (NULL);
    return (xmlDoRead(ctxt, URL, encoding, options, 0));
}