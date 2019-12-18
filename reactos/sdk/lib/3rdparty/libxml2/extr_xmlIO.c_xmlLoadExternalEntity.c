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
typedef  int /*<<< orphan*/  xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 scalar_t__ xmlCanonicPath (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlCurrentExternalEntityLoader (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlIOErrMemory (char*) ; 
 scalar_t__ xmlNoNetExists (char const*) ; 

xmlParserInputPtr
xmlLoadExternalEntity(const char *URL, const char *ID,
                      xmlParserCtxtPtr ctxt) {
    if ((URL != NULL) && (xmlNoNetExists(URL) == 0)) {
	char *canonicFilename;
	xmlParserInputPtr ret;

	canonicFilename = (char *) xmlCanonicPath((const xmlChar *) URL);
	if (canonicFilename == NULL) {
            xmlIOErrMemory("building canonical path\n");
	    return(NULL);
	}

	ret = xmlCurrentExternalEntityLoader(canonicFilename, ID, ctxt);
	xmlFree(canonicFilename);
	return(ret);
    }
    return(xmlCurrentExternalEntityLoader(URL, ID, ctxt));
}