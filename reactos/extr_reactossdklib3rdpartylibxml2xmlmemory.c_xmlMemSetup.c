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
typedef  int /*<<< orphan*/ * xmlStrdupFunc ;
typedef  int /*<<< orphan*/ * xmlReallocFunc ;
typedef  int /*<<< orphan*/ * xmlMallocFunc ;
typedef  int /*<<< orphan*/ * xmlFreeFunc ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlFree ; 
 int /*<<< orphan*/ * xmlMalloc ; 
 int /*<<< orphan*/ * xmlMallocAtomic ; 
 int /*<<< orphan*/ * xmlMemStrdup ; 
 int /*<<< orphan*/ * xmlRealloc ; 

int
xmlMemSetup(xmlFreeFunc freeFunc, xmlMallocFunc mallocFunc,
            xmlReallocFunc reallocFunc, xmlStrdupFunc strdupFunc) {
#ifdef DEBUG_MEMORY
     xmlGenericError(xmlGenericErrorContext,
	     "xmlMemSetup()\n");
#endif
    if (freeFunc == NULL)
	return(-1);
    if (mallocFunc == NULL)
	return(-1);
    if (reallocFunc == NULL)
	return(-1);
    if (strdupFunc == NULL)
	return(-1);
    xmlFree = freeFunc;
    xmlMalloc = mallocFunc;
    xmlMallocAtomic = mallocFunc;
    xmlRealloc = reallocFunc;
    xmlMemStrdup = strdupFunc;
#ifdef DEBUG_MEMORY
     xmlGenericError(xmlGenericErrorContext,
	     "xmlMemSetup() Ok\n");
#endif
    return(0);
}