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
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;

/* Variables and functions */
 int /*<<< orphan*/  inputPush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlCtxtReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlDoRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  xmlInitParser () ; 
 int /*<<< orphan*/ * xmlLoadExternalEntity (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

xmlDocPtr
xmlCtxtReadFile(xmlParserCtxtPtr ctxt, const char *filename,
                const char *encoding, int options)
{
    xmlParserInputPtr stream;

    if (filename == NULL)
        return (NULL);
    if (ctxt == NULL)
        return (NULL);
    xmlInitParser();

    xmlCtxtReset(ctxt);

    stream = xmlLoadExternalEntity(filename, NULL, ctxt);
    if (stream == NULL) {
        return (NULL);
    }
    inputPush(ctxt, stream);
    return (xmlDoRead(ctxt, NULL, encoding, options, 1));
}