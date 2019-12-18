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
 int /*<<< orphan*/  __xmlGlobalInitMutexLock () ; 
 int /*<<< orphan*/  __xmlGlobalInitMutexUnlock () ; 
 int /*<<< orphan*/  htmlDefaultSAXHandlerInit () ; 
 int /*<<< orphan*/  htmlInitAutoClose () ; 
 int /*<<< orphan*/  initGenericErrorDefaultFunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlDefaultSAXHandlerInit () ; 
 int /*<<< orphan*/ * xmlGenericError ; 
 int /*<<< orphan*/ * xmlGenericErrorDefaultFunc ; 
 int /*<<< orphan*/  xmlInitCharEncodingHandlers () ; 
 int /*<<< orphan*/  xmlInitGlobals () ; 
 int /*<<< orphan*/  xmlInitMemory () ; 
 int /*<<< orphan*/  xmlInitThreads () ; 
 int /*<<< orphan*/  xmlInitializeDict () ; 
 int xmlParserInitialized ; 
 int /*<<< orphan*/  xmlRegisterDefaultInputCallbacks () ; 
 int /*<<< orphan*/  xmlRegisterDefaultOutputCallbacks () ; 
 int /*<<< orphan*/  xmlXPathInit () ; 

void
xmlInitParser(void) {
    if (xmlParserInitialized != 0)
	return;

#ifdef LIBXML_THREAD_ENABLED
    __xmlGlobalInitMutexLock();
    if (xmlParserInitialized == 0) {
#endif
	xmlInitThreads();
	xmlInitGlobals();
	if ((xmlGenericError == xmlGenericErrorDefaultFunc) ||
	    (xmlGenericError == NULL))
	    initGenericErrorDefaultFunc(NULL);
	xmlInitMemory();
        xmlInitializeDict();
	xmlInitCharEncodingHandlers();
	xmlDefaultSAXHandlerInit();
	xmlRegisterDefaultInputCallbacks();
#ifdef LIBXML_OUTPUT_ENABLED
	xmlRegisterDefaultOutputCallbacks();
#endif /* LIBXML_OUTPUT_ENABLED */
#ifdef LIBXML_HTML_ENABLED
	htmlInitAutoClose();
	htmlDefaultSAXHandlerInit();
#endif
#ifdef LIBXML_XPATH_ENABLED
	xmlXPathInit();
#endif
	xmlParserInitialized = 1;
#ifdef LIBXML_THREAD_ENABLED
    }
    __xmlGlobalInitMutexUnlock();
#endif
}