#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_8__ {int linenumbers; char* directory; } ;

/* Variables and functions */
 int /*<<< orphan*/  inputPush (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlCtxtUseOptionsInternal (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlErrMemory (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_1__*) ; 
 int /*<<< orphan*/ * xmlLoadExternalEntity (char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* xmlNewParserCtxt () ; 
 char* xmlParserGetDirectory (char const*) ; 

xmlParserCtxtPtr
xmlCreateURLParserCtxt(const char *filename, int options)
{
    xmlParserCtxtPtr ctxt;
    xmlParserInputPtr inputStream;
    char *directory = NULL;

    ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
	xmlErrMemory(NULL, "cannot allocate parser context");
	return(NULL);
    }

    if (options)
	xmlCtxtUseOptionsInternal(ctxt, options, NULL);
    ctxt->linenumbers = 1;

    inputStream = xmlLoadExternalEntity(filename, NULL, ctxt);
    if (inputStream == NULL) {
	xmlFreeParserCtxt(ctxt);
	return(NULL);
    }

    inputPush(ctxt, inputStream);
    if ((ctxt->directory == NULL) && (directory == NULL))
        directory = xmlParserGetDirectory(filename);
    if ((ctxt->directory == NULL) && (directory != NULL))
        ctxt->directory = directory;

    return(ctxt);
}