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
 int /*<<< orphan*/  xmlCatalogCleanup () ; 
 int /*<<< orphan*/  xmlCleanupCharEncodingHandlers () ; 
 int /*<<< orphan*/  xmlCleanupGlobals () ; 
 int /*<<< orphan*/  xmlCleanupInputCallbacks () ; 
 int /*<<< orphan*/  xmlCleanupMemory () ; 
 int /*<<< orphan*/  xmlCleanupOutputCallbacks () ; 
 int /*<<< orphan*/  xmlCleanupThreads () ; 
 int /*<<< orphan*/  xmlDictCleanup () ; 
 scalar_t__ xmlParserInitialized ; 
 int /*<<< orphan*/  xmlRelaxNGCleanupTypes () ; 
 int /*<<< orphan*/  xmlResetLastError () ; 
 int /*<<< orphan*/  xmlSchemaCleanupTypes () ; 

void
xmlCleanupParser(void) {
    if (!xmlParserInitialized)
	return;

    xmlCleanupCharEncodingHandlers();
#ifdef LIBXML_CATALOG_ENABLED
    xmlCatalogCleanup();
#endif
    xmlDictCleanup();
    xmlCleanupInputCallbacks();
#ifdef LIBXML_OUTPUT_ENABLED
    xmlCleanupOutputCallbacks();
#endif
#ifdef LIBXML_SCHEMAS_ENABLED
    xmlSchemaCleanupTypes();
    xmlRelaxNGCleanupTypes();
#endif
    xmlResetLastError();
    xmlCleanupGlobals();
    xmlCleanupThreads(); /* must be last if called not from the main thread */
    xmlCleanupMemory();
    xmlParserInitialized = 0;
}