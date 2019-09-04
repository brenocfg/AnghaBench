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
typedef  int /*<<< orphan*/  xmlStrdupFunc ;
typedef  int /*<<< orphan*/  xmlReallocFunc ;
typedef  int /*<<< orphan*/  xmlMallocFunc ;
typedef  int /*<<< orphan*/  xmlFreeFunc ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree ; 
 int /*<<< orphan*/  xmlMalloc ; 
 int /*<<< orphan*/  xmlMallocAtomic ; 
 int /*<<< orphan*/  xmlMemStrdup ; 
 int /*<<< orphan*/  xmlRealloc ; 

int
xmlGcMemGet(xmlFreeFunc *freeFunc, xmlMallocFunc *mallocFunc,
            xmlMallocFunc *mallocAtomicFunc, xmlReallocFunc *reallocFunc,
	    xmlStrdupFunc *strdupFunc) {
    if (freeFunc != NULL) *freeFunc = xmlFree;
    if (mallocFunc != NULL) *mallocFunc = xmlMalloc;
    if (mallocAtomicFunc != NULL) *mallocAtomicFunc = xmlMallocAtomic;
    if (reallocFunc != NULL) *reallocFunc = xmlRealloc;
    if (strdupFunc != NULL) *strdupFunc = xmlMemStrdup;
    return(0);
}