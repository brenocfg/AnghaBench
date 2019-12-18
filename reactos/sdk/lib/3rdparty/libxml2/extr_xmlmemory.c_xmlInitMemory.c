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

/* Variables and functions */
 char* getenv (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 int xmlMemInitialized ; 
 int /*<<< orphan*/  xmlMemMutex ; 
 int /*<<< orphan*/  xmlMemStopAtBlock ; 
 int /*<<< orphan*/  xmlMemTraceBlockAt ; 
 int /*<<< orphan*/  xmlNewMutex () ; 

int
xmlInitMemory(void)
{
#ifdef HAVE_STDLIB_H
     char *breakpoint;
#endif
#ifdef DEBUG_MEMORY
     xmlGenericError(xmlGenericErrorContext,
	     "xmlInitMemory()\n");
#endif
    /*
     This is really not good code (see Bug 130419).  Suggestions for
     improvement will be welcome!
    */
     if (xmlMemInitialized) return(-1);
     xmlMemInitialized = 1;
     xmlMemMutex = xmlNewMutex();

#ifdef HAVE_STDLIB_H
     breakpoint = getenv("XML_MEM_BREAKPOINT");
     if (breakpoint != NULL) {
         sscanf(breakpoint, "%ud", &xmlMemStopAtBlock);
     }
#endif
#ifdef HAVE_STDLIB_H
     breakpoint = getenv("XML_MEM_TRACE");
     if (breakpoint != NULL) {
         sscanf(breakpoint, "%p", &xmlMemTraceBlockAt);
     }
#endif

#ifdef DEBUG_MEMORY
     xmlGenericError(xmlGenericErrorContext,
	     "xmlInitMemory() Ok\n");
#endif
     return(0);
}